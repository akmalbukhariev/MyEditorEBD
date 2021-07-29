#include "ReadSstFile.h"

#include <qmath.h>
 
ReadSstFile::ReadSstFile(const QString& fileName, QObject* parent)
	:ReadFile(fileName, parent)
{
	_suffix = Sst;
	_fileName = fileName;
}

ReadSstFile::~ReadSstFile()
{
}

bool ReadSstFile::read(EbdFileInfo& ebdFile, bool readThumbnail)
{
	char FUNCTION_FILTER = 0x0F;

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
	SstHeader sstHeader;
	
	file.seek(0);

	uint sizeSS = sizeof(sstHeader);
	char* ssHeaderData = new char[sizeSS];
	memset(ssHeaderData, 0, sizeSS);

	stream.readRawData(ssHeaderData, sizeSS);
	sstHeader = Control::instance()->byteToStruct(ssHeaderData, sstHeader);

	file.seek(0xA0);
	
	// 스티치 데이터만 가져옴. 3byte 데이터가 잘린 부분은 버림
	long nReable = (file.size() - file.pos()) % 3;
	nReable = file.size() - file.pos() - nReable;
	 
	int dCount = nReable + 3;
	char* readStitchByte = new char[dCount];
	memset(readStitchByte, 0, nReable);

	stream.readRawData(readStitchByte, nReable);
	
	short sumX = 0;
	short sumY = 0;
	bool sequin_start = false;

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
		int dXMoved = readStitchByte[i];
		int dYMoved = readStitchByte[i + 1];
		int dFData = readStitchByte[i + 2];

		int dxSign = getBit(readStitchByte[i + 2], 6) == 1 ? -1 : 1;
		int dySign = getBit(readStitchByte[i + 2], 4) == 1 ? 1 : -1;

		X = qRound((double)(dXMoved & 0x7F) * dxSign);
		Y = qRound((double)(dYMoved & 0x7F) * dySign);

		sumX += X;
		sumY += Y;

		ebdFile.ebdHeader.Plus_x  = qMax(ebdFile.ebdHeader.Plus_x, sumX);
		ebdFile.ebdHeader.Minus_x = qMin(ebdFile.ebdHeader.Minus_x, sumX);
		ebdFile.ebdHeader.Plus_y  = qMax(ebdFile.ebdHeader.Plus_y, sumY);
		ebdFile.ebdHeader.Minus_y = qMin(ebdFile.ebdHeader.Minus_y, sumY);

		Func = ((dYMoved & 0x80) == 1) ? ((dFData & 0x0F) | 0x80) : (dFData & 0x0F);

		if ((Func & FUNCTION_FILTER) == 0x05)	   sequin_start = true;
		else if ((Func & FUNCTION_FILTER) == 0x06) sequin_start = false;

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

			switch (Func & FUNCTION_FILTER)
			{
				case JUMP_CODE:
				{
					jumpCount++;
					if (jumpCount == 3)
					{	
						jumpCount = 0;
					}

					if (sequin_start == false)
						ebdFile.ebdHeader.JumpNum++;
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
				default:
					jumpCount = 0; break;
			}

			x1 = nextPoint.x();
			y1 = nextPoint.y();
		}

		if (sequin_start == true && (Func & FUNCTION_FILTER) == JUMP_CODE)
		{
			Func = (Func & 0xF0);
			Func = (Func | FRONTSQ_CODE);
		}

		ebdFile.ebdHeader.StitchCount++;

		if (Func == END_CODE)
			break;
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

	QString temp = QString(sstHeader.Name).trimmed();
	ebdFile.ebdHeader.DesignName = (quint8*)sstHeader.Name;
	ebdFile.ebdHeader.FileNameLength = QFileInfo(_fileName).baseName().length();
	ebdFile.ebdHeader.FileName = (quint8*)QFileInfo(_fileName).baseName().toStdString().c_str();
	ebdFile.ebdHeader.DesignLock = 0;

	return true;
}
