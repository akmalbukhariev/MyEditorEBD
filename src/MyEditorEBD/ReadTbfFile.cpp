#include "ReadTbfFile.h"

ReadTbfFile::ReadTbfFile(const QString& fileName, QObject* parent)
	:ReadFile(fileName, parent)
{
	_suffix = Tbf;
	_fileName = fileName;
}

ReadTbfFile::~ReadTbfFile()
{
}

bool ReadTbfFile::read(EbdFileInfo& ebdFile, bool readThumbnail)
{
	QList<HeaderDataInfo> hList;

	_defaultColorCount = 0;

	if (!checkFile()) return false;

	HeaderDataInfo hInfo;

	QFile file(_fileName);
	if (!file.open(QIODevice::ReadOnly))
	{
		_errorString = "Could not read this file.";
		return false;
	}

	QDataStream stream(&file);

	file.seek(0x80);

	char* la = new char[3];
	memset(la, 0, 3);
	stream.readRawData(la, 3);
	QString strLA = QString::fromUtf8(la);
	//getRealString(strLA);

	if (strLA.contains("LA:"))
	{
		char* designName = new char[16];
		memset(designName, 0, 16);
		stream.readRawData(designName, 16);

		ebdFile.ebdHeader.DesignName = (quint8*)designName;
	}

	file.seek(0x10a);

	ushort* CcTemp = new ushort[4000];
	int count = 1;
	for (count = 1; count < 4000; count++)
	{
		ushort tData;
		stream.readRawData((char*)&tData, sizeof(ushort));
		if ((CcTemp[count] = tData) == 0)
			break;
	}

	ebdFile.ebdHeader.CCTableData.reserve(count);

	for(int i = 1; i < count; i++)
		ebdFile.ebdHeader.CCTableData[i].Needle = (ushort)(((CcTemp[i] >> 4 & 0x0f) * 10) + (CcTemp[i] & 0x0f));

	ebdFile.ebdHeader.CCTableSize = (uint)(ebdFile.ebdHeader.CCTableData.count() * 8);

	file.seek(0x600);

	// 스티치 데이터만 가져옴. 3byte 데이터가 잘린 부분은 버림
	long nReable = (file.size() - file.pos()) % 3;
	nReable = file.size() - file.pos() - nReable;

	int dCount = nReable + 3;
	char* readStitchByte = new char[dCount];
	memset(readStitchByte, 0, nReable);

	stream.readRawData(readStitchByte, nReable);
	readStitchByte[nReable + 3 - 1] = 0x8f;

	short sumX = 0;
	short sumY = 0;

	float x1 = 0;
	float y1 = 0;
	int colorIndex = 1;

	signed char X;
	signed char Y;
	unsigned char Func;

	DataDesign* dParts;
	QList<LinePoint> pList;

	if (!readThumbnail)
	{
		dParts = new DataDesign();
	}

	for (int i = 0; i < 15; i++)
	{
		ebdFile.defaultPalettes.append(getDefaultColor());
	}

	int jumpCount = 0;
	for (int i = 0; i < dCount; i += 3)
	{
		X = qRound((double)readStitchByte[i]);
		Y = qRound((double)readStitchByte[i + 1]);
		Func = readStitchByte[i + 2];

		sumX += X;
		sumY += Y;

		ebdFile.ebdHeader.Plus_x = qMax(ebdFile.ebdHeader.Plus_x, sumX);
		ebdFile.ebdHeader.Minus_x = qMin(ebdFile.ebdHeader.Minus_x, sumX);
		ebdFile.ebdHeader.Plus_y = qMax(ebdFile.ebdHeader.Plus_y, sumY);
		ebdFile.ebdHeader.Minus_y = qMin(ebdFile.ebdHeader.Minus_y, sumY);

		if (readThumbnail)
		{
			ebdFile.points.append(PointData(QPointF(X, Y), Func));
		}
		else
		{
			//Sum funtion code color & jump
			switch (Func)
			{
			case 0x80:
				Func = NORMAL_CODE;
				break;
			case 0x86:
				Func = TRIM_CODE;
				break;
			case 0x90:
				Func = JUMP_CODE;
				ebdFile.ebdHeader.JumpNum++;
				break;
			case 0x81:
				Func = CC_CODE;
				ebdFile.ebdHeader.ColorChangeNum++;
				break;
			case 0x4d:
				Func = SQSTART_CODE;
				break;
			case 0x89:
				Func = FRONTSQ_CODE;
				break;
			case 0x69:
				Func = REARSQ_CODE;
				break;
			case 0x88:
				Func = SQEND_CODE;
				break;
			case 0x8f:
				Func = END_CODE;
				break;
			default:
				if (X == 0 && Y == 0)
					continue;
				else
					Func = NORMAL_CODE;
				break;
			}

			float x2 = X;
			float y2 = Y;

			x2 = x2 / 10;
			y2 = y2 / 10;

			QPointF nextPoint = _calcPoint.calcNextPoint(x1, y1, x2, y2);

			LinePoint lPoint = LinePoint(QPointF(x1, y1), QPointF(nextPoint.x(), nextPoint.y()));
			lPoint.type = (TypeOfFunction)Func;
			lPoint.realPoint = QPointF(X, Y); //lPoint.calcDiffXY();

			pList.append(lPoint);

			switch (Func)
			{
			case JUMP_CODE:
				jumpCount++;
				if (jumpCount == 3)
				{	
					jumpCount = 0;
				}
				break;
			case CC_CODE:
			{
				colorIndex++;
				ebdFile.ebdHeader.ColorChangeNum++;

				DesignPart dPart(i, pList);

				if (_defaultColorCount < 15)
				{
					dPart.lineColor = ebdFile.defaultPalettes[_defaultColorCount];
					dPart.colorIndex = _defaultColorCount;
					_defaultColorCount++;
				}
				else
				{
					_defaultColorCount = 0;
				}

				dParts->append(dPart);
				pList.clear();
			}
			break;
			case END_CODE:
				break;
			}

			x1 = nextPoint.x();
			y1 = nextPoint.y();
		}
	}

	if (!readThumbnail)
	{
		int id = 0;
		if (dParts->count() != 0 && pList.count() != 0)
		{
			id = dParts->at(dParts->count() - 1).id + 1;

			DesignPart dPart(id, pList);
			 
			if (_defaultColorCount == 15)
				_defaultColorCount = 0;

			dPart.lineColor = ebdFile.defaultPalettes[_defaultColorCount];
			dPart.colorIndex = _defaultColorCount;

			dParts->append(dPart);
		}

		ebdFile.dParts = dParts;
	}

	ebdFile.ebdHeader.FileNameLength = QFileInfo(_fileName).baseName().length();
	ebdFile.ebdHeader.FileName = (quint8*)QFileInfo(_fileName).baseName().toStdString().c_str();
	ebdFile.ebdHeader.DesignLock = 0;
	ebdFile.ebdHeader.StitchCount = ebdFile.getCountOfData();

	return true;
}