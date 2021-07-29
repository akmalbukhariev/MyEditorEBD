#include "ReadDstFile.h"

ReadDstFile::ReadDstFile(const QString& fileName, QObject* parent)
	:ReadFile(fileName, parent)
{
	_suffix = Dst;
	_fileName = fileName;
}

ReadDstFile::~ReadDstFile()
{
}
 
bool ReadDstFile::read(EbdFileInfo& ebdFile, bool readThumbnail)
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

	file.seek(0);

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

	file.seek(0x0200);

	// 스티치 데이터만 가져옴. 3byte 데이터가 잘린 부분은 버림
	long nReable = (file.size() - file.pos()) % 3;
	nReable = file.size() - file.pos() - nReable;

	int dCount = nReable + 3;
	char* readStitchByte = new char[dCount];
	memset(readStitchByte, 0, nReable);

	stream.readRawData(readStitchByte, nReable);
	readStitchByte[nReable + 3 - 1] = 0xf3;

	short sumX = 0;
	short sumY = 0;
	bool sequin = false;

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
		X = decodeDstDx(readStitchByte[i], readStitchByte[i + 1], readStitchByte[i + 2]);
		Y = decodeDstDy(readStitchByte[i], readStitchByte[i + 1], readStitchByte[i + 2]);

		sumX += X;
		sumY += Y;

		ebdFile.ebdHeader.Plus_x = qMax(ebdFile.ebdHeader.Plus_x, sumX);
		ebdFile.ebdHeader.Minus_x = qMin(ebdFile.ebdHeader.Minus_x, sumX);
		ebdFile.ebdHeader.Plus_y = qMax(ebdFile.ebdHeader.Plus_y, sumY);
		ebdFile.ebdHeader.Minus_y = qMin(ebdFile.ebdHeader.Minus_y, sumY);

		Func = decodeDstFunction(readStitchByte[i + 2], sequin);

		if (readThumbnail)
		{
			ebdFile.points.append(PointData(QPointF(X, Y), Func));
		}
		else 
		{
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
					ebdFile.ebdHeader.JumpNum++;
					break;
				case CC_CODE:
				{
					colorIndex++;

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

					ebdFile.ebdHeader.ColorChangeNum++;
				}
				break;
				case END_CODE:
					break;
				case 0xFF: //Error
					return false;
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

	//마지막 지점에 엔드 코드가 없으면 넣어야함
	/*if (readStitchList[readStitchList.Count - 1].FN != END_CODE)
	{
		X = 0;
		Y = 0;
		Func = END_CODE;
	}*/

	ebdFile.ebdHeader.FileNameLength = QFileInfo(_fileName).absoluteFilePath().length();
	ebdFile.ebdHeader.FileName = (quint8*)(QFileInfo(_fileName).baseName()).toStdString().c_str();
	ebdFile.ebdHeader.DesignLock = 0;
	return true;
}
