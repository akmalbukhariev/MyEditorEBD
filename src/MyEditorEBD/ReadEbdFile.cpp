#include "ReadEbdFile.h"

#include <QDebug>
#include <QtEndian>
#include <Qsettings> 
#include <QFileDialog> 

ReadEbdFile::ReadEbdFile(const QString& fileName, QObject* parent)
	:ReadFile(fileName, parent)
{
	_suffix = Ebd;
	_fileName = fileName;
}

ReadEbdFile::~ReadEbdFile()
{

}

bool ReadEbdFile::read(EbdFileInfo& ebdFile, bool readThumbnail)
{
	quint16 FileId			 = 0x0EBD;
	quint16 DesignId		 = 0xA001;
	quint16 ColorPaletteId	 = 0xB001;
	quint16 ColorFilmID		 = 0xB007;
	quint16 TableId			 = 0xB002;
	quint16 ThumbnailId		 = 0xB003;
	quint16 WorkInfoId		 = 0xB005;
	quint16 DataId			 = 0xB004;
	quint16 DesignPara		 = 0xB006;
	quint16 McColorPaletteId = 0xB008;
	quint16 ReservedId		 = 0xC001;

	_defaultColorCount = 0;

	QList<HeaderDataInfo> hList;

	if (!checkFile()) return false;
	
	HeaderDataInfo hInfo;

	quint16 hData;

	QFile file(_fileName);
	if (!file.open(QIODevice::ReadOnly))
	{
		_errorString = "Could not read this file.";
		return false;
	}

	QDataStream stream(&file);
	
	#pragma region Signature ID Required
	
	stream.readRawData((char*)&hData, sizeof(quint16));
	if (FileId == hData)
		hList.append(HeaderDataInfo("File suffix", "EBD"));
	else
	{
		_errorString = "File suffix is wrong.";
		return false;
	}

	quint8 hDataS;
	stream.readRawData((char*)&hDataS, sizeof(quint8));
	hList.append(HeaderDataInfo("Major value", QString::number(hDataS)));

	stream.readRawData((char*)&hDataS, sizeof(quint8));
	hList.append(HeaderDataInfo("Minor value", QString::number(hDataS)));
	
	#pragma endregion 

	#pragma region Design Info ID Required	

	stream.readRawData((char*)&hData, sizeof(quint16));
	if (DesignId == hData)
		hList.append(HeaderDataInfo("Design information", ""));
	else
	{
		_errorString = "Design information is wrong.";
		return false;
	}

	quint32 totalSize;
	stream.readRawData((char*)&totalSize, sizeof(quint32));
	ebdFile.ebdHeader.TotalHeaderSize = totalSize;
	hList.append(HeaderDataInfo("Total Header size", QString::number(totalSize)));

	quint32 designInfoSize;
	stream.readRawData((char*)&designInfoSize, sizeof(quint32));
	ebdFile.ebdHeader.HeaderSize = designInfoSize;
	hList.append(HeaderDataInfo("Design information size", QString::number(designInfoSize)));

	quint32 totalStitchCount;
	stream.readRawData((char*)&totalStitchCount, sizeof(quint32));  
	ebdFile.ebdHeader.StitchCount = totalStitchCount;
	hList.append(HeaderDataInfo("Total stitch count", QString::number(totalStitchCount)));

	signed short plusX;
	stream.readRawData((char*)&plusX, sizeof(signed short));
	ebdFile.ebdHeader.Plus_x = plusX;
	hList.append(HeaderDataInfo("Plus X size", QString::number(plusX)));

	signed short plusY;
	stream.readRawData((char*)&plusY, sizeof(signed short));
	ebdFile.ebdHeader.Plus_y = plusY;
	hList.append(HeaderDataInfo("Plus Y size", QString::number(plusY)));

	signed short minusX;
	stream.readRawData((char*)&minusX, sizeof(signed short));
	ebdFile.ebdHeader.Minus_x = minusX;
	hList.append(HeaderDataInfo("Minus X size", QString::number(minusX)));

	signed short minusY;
	stream.readRawData((char*)&minusY, sizeof(signed short));
	ebdFile.ebdHeader.Minus_y = minusY;
	hList.append(HeaderDataInfo("Minus Y size", QString::number(minusY)));

	signed short gapX;
	stream.readRawData((char*)&gapX, sizeof(signed short));
	ebdFile.ebdHeader.Gap_x = gapX;
	hList.append(HeaderDataInfo("Gap X", QString::number(gapX)));

	signed short gapY;
	stream.readRawData((char*)&gapY, sizeof(signed short));  
	ebdFile.ebdHeader.Gap_y = gapY;
	hList.append(HeaderDataInfo("Gap Y", QString::number(gapY)));

	stream.readRawData((char*)&hData, sizeof(quint16));
	ebdFile.ebdHeader.DesignLock = hData;
	hList.append(HeaderDataInfo("Design lock", QString::number(hData)));

	stream.readRawData((char*)&hData, sizeof(quint16));  
	ebdFile.ebdHeader.ColorChangeNum = hData;
	hList.append(HeaderDataInfo("Color part number", QString::number(hData)));

	quint32 jumpNumber;
	stream.readRawData((char*)&jumpNumber, sizeof(quint32));
	ebdFile.ebdHeader.JumpNum = jumpNumber;
	hList.append(HeaderDataInfo("Jump Number", QString::number(jumpNumber)));

	stream.readRawData((char*)&hData, sizeof(quint16));  
	ebdFile.ebdHeader.DesignNameLength = hData;
	hList.append(HeaderDataInfo("Design name length", QString::number(hData)));

	int length = (sizeof(quint8) * hData);
	quint8* designName = new quint8[length];
	memset(designName, 0, length);
	//designName[length] = '\0';

	QString strName = "";
	stream.readRawData((char*)designName, length);
	strName = QString((char*)designName);
	//getRealString(strName);
	ebdFile.ebdHeader.DesignName = designName;
	hList.append(HeaderDataInfo("Design name", strName));

	/*delete [] designName;
	designName = nullptr;*/

	stream.readRawData((char*)&hData, sizeof(quint16));
	ebdFile.ebdHeader.FileNameLength = hData;
	hList.append(HeaderDataInfo("File name length", QString::number(hData)));

	length = (sizeof(quint8) * hData);
	quint8* fileName = new quint8[length];
	memset(fileName, 0, length);
	//fileName[length] = '\0';

	stream.readRawData((char*)fileName, length);
	strName = QString((char*)fileName);
	//getRealString(strName);
	ebdFile.ebdHeader.FileName = fileName;
	hList.append(HeaderDataInfo("File name", strName));

	/*delete [] fileName;
	fileName = nullptr;*/
	#pragma endregion

	#pragma region Color palette table  ID

	stream.readRawData((char*)&hData, sizeof(quint16));
	if (ColorPaletteId == hData)
	{
		hList.append(HeaderDataInfo("Color palette", ""));

		quint32 colorSize;
		stream.readRawData((char*)&colorSize, sizeof(quint32));

		if (!colorSize == 0)
		{
			ebdFile.ebdHeader.ColorPaletteSize = colorSize;
			hList.append(HeaderDataInfo("Color size", QString::number(colorSize)));

			if (ebdFile.ebdHeader.ColorPaletteSize != 0)
			{
				quint32 count = ebdFile.ebdHeader.ColorPaletteSize / 4;
				ebdFile.ebdHeader.ColorPaletteData = new quint32[count];
				memset(ebdFile.ebdHeader.ColorPaletteData, 0, sizeof(quint32));

				for (int i = 0; i < count; i++)
					stream.readRawData((char*)&ebdFile.ebdHeader.ColorPaletteData[i], sizeof(quint32));
			}
		}
		stream.readRawData((char*)&hData, sizeof(quint16));

		/*quint8 R;
		quint8 G;
		quint8 B;
		quint8 needle = 0;

		for (int i = 0; i < colorSize; i += 4)
		{
			stream.readRawData((char*)&needle, sizeof(quint8)); //1 ~ 15
			stream.readRawData((char*)&R, sizeof(quint8));
			stream.readRawData((char*)&G, sizeof(quint8));
			stream.readRawData((char*)&B, sizeof(quint8));

			if (needle == 0 || needle > 16) continue;
			ebdFile.ebdHeader.ColorData.append(NeedleColor(QColor(R, G, B), needle));
		}*/
	}

	#pragma endregion

	#pragma region Used sequence of color palette ID
	
	if (ColorFilmID == hData)
	{
		hList.append(HeaderDataInfo("Color film", ""));

		quint32 filmSize;
		stream.readRawData((char*)&filmSize, sizeof(quint32));
		ebdFile.ebdHeader.ColorFilmDataSize = filmSize;
		hList.append(HeaderDataInfo("Color size", QString::number(filmSize)));

		if (ebdFile.ebdHeader.ColorFilmDataSize != 0)
		{
			quint32 count = ebdFile.ebdHeader.ColorFilmDataSize / 3;

			for (int i = 0; i < count; i++)
			{
				char Sequin;
				stream.readRawData((char*)&Sequin, sizeof(char));

				char WorkType;
				stream.readRawData((char*)&WorkType, sizeof(char));

				char PalletIndex;
				stream.readRawData((char*)&PalletIndex, sizeof(char));
				
				ebdFile.ebdHeader.ColorFilmData.append(ColorFilmStruct(Sequin, WorkType, PalletIndex));
			}
		}

		stream.readRawData((char*)&hData, sizeof(quint16));
	}

	#pragma endregion

	#pragma region C/C table ID

	if (TableId == hData)
	{
		hList.append(HeaderDataInfo("C/C Information", ""));

		quint32 tableSize;
		stream.readRawData((char*)&tableSize, sizeof(quint32));
		ebdFile.ebdHeader.CCTableSize = tableSize;
		hList.append(HeaderDataInfo("Table size", QString::number(tableSize)));

		length = sizeof(quint8) * tableSize;
		quint16 Needle;
		quint16 Type;
		quint16 Height;
		quint16 Group;

		quint32 count = tableSize / 8;

		for (int i = 0; i < count; i++)
		{
			stream.readRawData((char*)&Needle, sizeof(quint16));
			stream.readRawData((char*)&Group, sizeof(quint16));
			stream.readRawData((char*)&Height, sizeof(quint16));
			stream.readRawData((char*)&Type, sizeof(quint16));

			ebdFile.ebdHeader.CCTableData.append(NeedleSet(Needle, Type, Height, Group));
		}

		stream.readRawData((char*)&hData, sizeof(quint16));
	}

	#pragma endregion

	#pragma region Thumbnail ID Required

	if (ThumbnailId == hData)
	{
		hList.append(HeaderDataInfo("Thumbnail information", ""));
	}
	else
	{
		_errorString = "Thumbnail information is wrong.";
		return false;
	}

	quint32 thumbNailSize;
	stream.readRawData((char*)&thumbNailSize, sizeof(quint32));
	ebdFile.ebdHeader.ThumbNailSize = thumbNailSize;
	hList.append(HeaderDataInfo("Thumbnail size", QString::number(thumbNailSize)));

	length = sizeof(quint8) * thumbNailSize;

	QByteArray thumData64(thumbNailSize, 0);
	stream.readRawData(thumData64.data(), thumbNailSize);
	ebdFile.ebdHeader.ThumbNailData = thumData64;

	#pragma endregion

	#pragma region Work Info ID

	stream.readRawData((char*)&hData, sizeof(quint16));
	if (WorkInfoId == hData)
	{
		hList.append(HeaderDataInfo("Work info", ""));

		quint32 dataU32;
		stream.readRawData((char*)&dataU32, sizeof(quint32));
		ebdFile.ebdHeader.WorkInfoSize = dataU32;
		hList.append(HeaderDataInfo("Work info. data size", QString::number(dataU32)));

		stream.readRawData((char*)&hData, sizeof(quint16));
		ebdFile.ebdHeader.StartPointUse = hData;
		hList.append(HeaderDataInfo("Start point use or not", QString::number(hData)));

		stream.readRawData((char*)&dataU32, sizeof(quint32));
		ebdFile.ebdHeader.XStartGap = dataU32;
		hList.append(HeaderDataInfo("X Start point gap from center point X", QString::number(dataU32)));

		stream.readRawData((char*)&dataU32, sizeof(quint32));
		ebdFile.ebdHeader.YStartGap = dataU32;
		hList.append(HeaderDataInfo("Y Start point gap from center point Y", QString::number(dataU32)));

		stream.readRawData((char*)&hData, sizeof(quint16));
		ebdFile.ebdHeader.FrameHoopUse = hData;
		hList.append(HeaderDataInfo("Frame & Hoop Use", QString::number(hData)));

		stream.readRawData((char*)&hData, sizeof(quint16));
		ebdFile.ebdHeader.FrameType = hData;
		hList.append(HeaderDataInfo("Type of frame", QString::number(hData)));

		stream.readRawData((char*)&hData, sizeof(quint16));
		ebdFile.ebdHeader.HoopType = hData;
		hList.append(HeaderDataInfo("Type of hoop", QString::number(hData)));

		stream.readRawData((char*)&hData, sizeof(quint16));
		ebdFile.ebdHeader.WorkAreaWidth = hData;
		hList.append(HeaderDataInfo("Work area width(X direction area)", QString::number(hData)));

		stream.readRawData((char*)&hData, sizeof(quint16));
		ebdFile.ebdHeader.WorkAreaHeight = hData;
		hList.append(HeaderDataInfo("Work area height(Y direction area)", QString::number(hData)));

		stream.readRawData((char*)&hData, sizeof(quint16));
		ebdFile.ebdHeader.PhysicalXSpace = hData;
		hList.append(HeaderDataInfo("Machine physical work area width", QString::number(hData)));

		stream.readRawData((char*)&hData, sizeof(quint16));
		ebdFile.ebdHeader.PhysicalYSpace = hData;
		hList.append(HeaderDataInfo("Machine physical work area height", QString::number(hData)));

		stream.readRawData((char*)&hData, sizeof(quint16));
		ebdFile.ebdHeader.Dummy16_1 = hData;
		hList.append(HeaderDataInfo("Reserved", QString::number(hData)));

		stream.readRawData((char*)&hData, sizeof(quint16));
		ebdFile.ebdHeader.Dummy16_2 = hData;
		hList.append(HeaderDataInfo("Reserved", QString::number(hData)));

		stream.readRawData((char*)&hData, sizeof(quint16));
		ebdFile.ebdHeader.Dummy16_3 = hData;
		hList.append(HeaderDataInfo("Reserved", QString::number(hData)));

		stream.readRawData((char*)&hData, sizeof(quint16));
		ebdFile.ebdHeader.Dummy16_4 = hData;
		hList.append(HeaderDataInfo("Reserved", QString::number(hData)));

		stream.readRawData((char*)&dataU32, sizeof(quint32));
		ebdFile.ebdHeader.Dummy32_1 = dataU32;
		hList.append(HeaderDataInfo("Reserved", QString::number(dataU32)));

		stream.readRawData((char*)&dataU32, sizeof(quint32));
		ebdFile.ebdHeader.Dummy32_2 = dataU32;
		hList.append(HeaderDataInfo("Reserved", QString::number(dataU32)));

		stream.readRawData((char*)&dataU32, sizeof(quint32));
		ebdFile.ebdHeader.Dummy32_3 = dataU32;
		hList.append(HeaderDataInfo("Reserved", QString::number(dataU32)));

		stream.readRawData((char*)&dataU32, sizeof(quint32));
		ebdFile.ebdHeader.Dummy32_4 = dataU32;
		hList.append(HeaderDataInfo("Reserved", QString::number(dataU32)));

		stream.readRawData((char*)&hData, sizeof(quint16));
	}

	#pragma endregion

	#pragma region Design Modify parameter

	if (DesignPara == hData)
	{
		hList.append(HeaderDataInfo("Design Modify Parameter", ""));

		quint32 dataU32;
		quint16 dataU16;

		stream.readRawData((char*)&dataU32, sizeof(quint32));
		ebdFile.ebdHeader.DesignParaSize = dataU32;
		hList.append(HeaderDataInfo("Design modify parameter data size", QString::number(dataU32)));

		stream.readRawData((char*)&dataU16, sizeof(quint16));
		ebdFile.ebdHeader.DesignModifyUse = dataU16;
		hList.append(HeaderDataInfo("Design modify parameter use ", QString::number(dataU16)));

		stream.readRawData((char*)&dataU16, sizeof(quint16));
		ebdFile.ebdHeader.Mirror = dataU16;
		hList.append(HeaderDataInfo("Mirror", QString::number(dataU16)));

		stream.readRawData((char*)&dataU16, sizeof(quint16));
		ebdFile.ebdHeader.XScale = dataU16;
		hList.append(HeaderDataInfo("X Scale", QString::number(dataU16)));

		stream.readRawData((char*)&dataU16, sizeof(quint16));
		ebdFile.ebdHeader.YScale = dataU16;
		hList.append(HeaderDataInfo("Y Scale", QString::number(dataU16)));

		stream.readRawData((char*)&dataU16, sizeof(quint16));
		ebdFile.ebdHeader.Angle = dataU16;
		hList.append(HeaderDataInfo("Angle", QString::number(dataU16)));

		stream.readRawData((char*)&dataU16, sizeof(quint16));
		ebdFile.ebdHeader.XSatin = dataU16;
		hList.append(HeaderDataInfo("X Satin", QString::number(dataU16)));

		stream.readRawData((char*)&dataU16, sizeof(quint16));
		ebdFile.ebdHeader.YSatin = dataU16;
		hList.append(HeaderDataInfo("Y Satin", QString::number(dataU16)));

		stream.readRawData((char*)&dataU32, sizeof(quint32));
		ebdFile.ebdHeader.StartStitch = dataU32;
		hList.append(HeaderDataInfo("Terminate stitch, start to this stitch count", QString::number(dataU32)));

		stream.readRawData((char*)&dataU16, sizeof(quint16));
		ebdFile.ebdHeader.StartEndFiltering = dataU16;
		hList.append(HeaderDataInfo("Filtering small stitch", QString::number(dataU16)));

		stream.readRawData((char*)&dataU16, sizeof(quint16));
		ebdFile.ebdHeader.Dummy_16_5 = dataU16;
		hList.append(HeaderDataInfo("Reserved", QString::number(dataU16)));

		stream.readRawData((char*)&dataU16, sizeof(quint16));
		ebdFile.ebdHeader.Dummy_16_6 = dataU16;
		hList.append(HeaderDataInfo("Reserved", QString::number(dataU16)));

		stream.readRawData((char*)&dataU16, sizeof(quint16));
		ebdFile.ebdHeader.Dummy_16_7 = dataU16;
		hList.append(HeaderDataInfo("Reserved", QString::number(dataU16)));

		stream.readRawData((char*)&dataU16, sizeof(quint16));
		ebdFile.ebdHeader.Dummy_16_8 = dataU16;
		hList.append(HeaderDataInfo("Reserved", QString::number(dataU16)));


		stream.readRawData((char*)&dataU32, sizeof(quint32));
		ebdFile.ebdHeader.Dummy_32_5 = dataU32;
		hList.append(HeaderDataInfo("Reserved", QString::number(dataU32)));

		stream.readRawData((char*)&dataU32, sizeof(quint32));
		ebdFile.ebdHeader.Dummy_32_6 = dataU32;
		hList.append(HeaderDataInfo("Reserved", QString::number(dataU32)));

		stream.readRawData((char*)&dataU32, sizeof(quint32));
		ebdFile.ebdHeader.Dummy_32_7 = dataU32;
		hList.append(HeaderDataInfo("Reserved", QString::number(dataU32)));

		stream.readRawData((char*)&dataU32, sizeof(quint32));
		ebdFile.ebdHeader.Dummy_32_8 = dataU32;
		hList.append(HeaderDataInfo("Reserved", QString::number(dataU32)));

		stream.readRawData((char*)&hData, sizeof(quint16));
	}

	#pragma endregion

	#pragma region Machine needle color palette ID
	
	if (McColorPaletteId == hData)
	{
		hList.append(HeaderDataInfo("MC Color palette", ""));

		quint32 colorSize;
		stream.readRawData((char*)&colorSize, sizeof(quint32));
		ebdFile.ebdHeader.MCColorPaletteDataSize = colorSize;
		hList.append(HeaderDataInfo("MC Color size", QString::number(colorSize)));

		if (ebdFile.ebdHeader.ColorPaletteSize != 0)
		{
			quint32 count = ebdFile.ebdHeader.MCColorPaletteDataSize / 4;
			ebdFile.ebdHeader.MCColorPaletteData = new quint32[count];
			memset(ebdFile.ebdHeader.MCColorPaletteData, 0, sizeof(quint32));

			for (int i = 0; i < count; i++)
				stream.readRawData((char*)&ebdFile.ebdHeader.MCColorPaletteData[i], sizeof(quint32));
		}

		stream.readRawData((char*)&hData, sizeof(quint16));
	}

	#pragma endregion

	if (readThumbnail)
	{
		ebdFile.headers = hList;
		return true;
	}

	#pragma region Design Data ID Required

	if (DataId == hData)
	{
		hList.append(HeaderDataInfo("Data information", ""));
	}
	else
	{
		_errorString = "Data information is wrong.";
		return false;
	}

	quint32 designSize;
	stream.readRawData((char*)&designSize, sizeof(quint32));
	ebdFile.ebdHeader.DesignDataSize = designSize;
	hList.append(HeaderDataInfo("Design size", QString::number(designSize)));

	length = sizeof(quint8) * designSize;

	readAllData(stream, length, ebdFile);

	#pragma endregion

	#pragma region Reserved ID

	stream.readRawData((char*)&hData, sizeof(quint16));
	if (ReservedId == hData)
	{
		hList.append(HeaderDataInfo("Reserved ID", ""));

		quint32 dataU32;
		stream.readRawData((char*)&dataU32, sizeof(quint32));
		hList.append(HeaderDataInfo("Reserved Size", QString::number(dataU32)));

		quint8 dataU8;
		stream.readRawData((char*)&dataU8, sizeof(quint8));
		hList.append(HeaderDataInfo("Reserved Data", QString::number(dataU8)));
	}

	#pragma endregion

	ebdFile.headers = hList;
	return true;
}

void ReadEbdFile::readAllData(QDataStream& stream, int length, EbdFileInfo& ebdInfo)
{
	signed char X;
	signed char Y;
	unsigned char Func;

	float x1 = 0;
	float y1 = 0;
	int colorIndex = 1;

	DataDesign* dParts = new DataDesign();
	QList<LinePoint> pList;
	QList<ColorFilmTable> colorFilmTable;

	ColorFilmStruct colorFilm;
	if(ebdInfo.ebdHeader.ColorFilmData.count() != 0)
		colorFilm = ebdInfo.ebdHeader.ColorFilmData[colorIndex];

	for (int i = 0; i < 15; i++)
	{
		ebdInfo.defaultPalettes.append(getDefaultColor());
	}

	int jumpCount = 0;
	for (int i = 0; i < length; i += 3)
	{
		stream.readRawData((char*)&X, sizeof(signed char));
		stream.readRawData((char*)&Y, sizeof(signed char));
		stream.readRawData((char*)&Func, sizeof(unsigned char));

		//qDebug() << i << "==>" << X << " : " << Y << " " << Func;

		float x2 = X;
		float y2 = Y;

		x2 = x2 / 10;
		y2 = y2 / 10;

		QPointF nextPoint = _calcPoint.calcNextPoint(x1, y1, x2, y2);

		LinePoint lPoint = LinePoint(QPointF(x1, y1), QPointF(nextPoint.x(), nextPoint.y()));
		lPoint.type = (TypeOfFunction)Func;
		lPoint.realPoint = QPointF(X, Y); //lPoint.calcDiffXY();

		pList.append(lPoint);

		ColorFilmStruct colorFilm;
		if (ebdInfo.ebdHeader.ColorFilmData.count() != 0)
			colorFilm = ebdInfo.ebdHeader.ColorFilmData[colorIndex];

		switch (Func)
		{
			case JUMP_CODE:
			{
				jumpCount++;
				if (jumpCount == 3)
				{
					/*DesignPart dPart(i, pList);
					dPart.colorIndex = colorIndex;

					for (int i = 0; i < ebdInfo.ebdHeader.ColorPaletteSize / 4; i++)
					{
						if (((ebdInfo.ebdHeader.ColorPaletteData[i] >> 24) & 0x000000FF) == colorFilm.PalletIndex)
						{
							int r = (ebdInfo.ebdHeader.ColorPaletteData[i] >> 16) & 0x00FFFFFF;
							int g = (ebdInfo.ebdHeader.ColorPaletteData[i] >> 8) & 0x00FFFFFF;
							int b = ebdInfo.ebdHeader.ColorPaletteData[i] & 0x00FFFFFF;

							dPart.lineColor = QPen(QColor(r, g, b));

							ebdInfo.colorFilmTable.append(ColorFilmTable(colorFilm.PalletIndex));
						}
					}

					dParts->append(dPart);

					pList.clear();*/
					jumpCount = 0;
				}
			}
			break;
			case CC_CODE:
			{
				colorIndex++;

				DesignPart dPart(i, pList);

				if (ebdInfo.ebdHeader.ColorPaletteSize == 0)
				{
					if (_defaultColorCount < 15)
					{
						dPart.lineColor = ebdInfo.defaultPalettes[_defaultColorCount];
						dPart.colorIndex = _defaultColorCount;
						_defaultColorCount++;
					}
					else
					{
						_defaultColorCount = 0;
					}
				}
				else
				{
					for (int i = 0; i < ebdInfo.ebdHeader.ColorPaletteSize / 4; i++)
					{
						int index = (ebdInfo.ebdHeader.ColorPaletteData[i] >> 24) & 0x000000FF;
						if (index == colorFilm.PalletIndex)
						{
							int r = (ebdInfo.ebdHeader.ColorPaletteData[i] >> 16) & 0x000000FF;
							int g = (ebdInfo.ebdHeader.ColorPaletteData[i] >> 8) & 0x000000FF;
							int b = ebdInfo.ebdHeader.ColorPaletteData[i] & 0x000000FF;

							dPart.lineColor = QPen(QColor(r, g, b));
							dPart.colorIndex = colorFilm.PalletIndex;

							ebdInfo.colorFilmTable.append(ColorFilmTable(colorFilm.PalletIndex, pList.count()));
						}
					}
				}

				dParts->append(dPart);
				pList.clear();
			}
			break;
		}

		x1 = nextPoint.x();
		y1 = nextPoint.y();
	}

	int id = 0;
	if (pList.count() != 0)
	{
		id = dParts->count() == 0 ? 1 : dParts->at(dParts->count() - 1).id + 1;

		DesignPart dPart(id, pList);

		if (ebdInfo.ebdHeader.ColorPaletteSize == 0)
		{
			if (_defaultColorCount == 15)
				_defaultColorCount = 0;

			dPart.lineColor = ebdInfo.defaultPalettes[_defaultColorCount];
			dPart.colorIndex = _defaultColorCount;
		}
		else
		{
			ColorFilmStruct colorFilm;
			if (ebdInfo.ebdHeader.ColorFilmData.count() != 0)
				colorFilm = ebdInfo.ebdHeader.ColorFilmData[colorIndex];

			for (int i = 0; i < ebdInfo.ebdHeader.ColorPaletteSize / 4; i++)
			{
				if (((ebdInfo.ebdHeader.ColorPaletteData[i] >> 24) & 0x000000FF) == colorFilm.PalletIndex)
				{
					int r = (ebdInfo.ebdHeader.ColorPaletteData[i] >> 16) & 0x000000FF;
					int g = (ebdInfo.ebdHeader.ColorPaletteData[i] >> 8) & 0x000000FF;
					int b = ebdInfo.ebdHeader.ColorPaletteData[i] & 0x000000FF;

					dPart.lineColor = QPen(QColor(r, g, b));
					dPart.colorIndex = colorFilm.PalletIndex;

					ebdInfo.colorFilmTable.append(ColorFilmTable(colorFilm.PalletIndex, pList.count()));
				}
			}

		}
		dParts->append(dPart);
	}

	ebdInfo.dParts = dParts;
}