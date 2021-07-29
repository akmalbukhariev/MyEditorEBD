#include "WriteEbdFile.h"

WriteEbdFile::WriteEbdFile(const QString& fileName, QObject *parent)
	: WriteFile(fileName, parent)
{
	_suffix = FileSuffix::Ebd;
}

WriteEbdFile::~WriteEbdFile()
{
}

bool WriteEbdFile::write(EbdFileInfo& ebdInfo)
{
	quint16 FileId = 0x0EBD;
	quint16 DesignId = 0xA001;
	quint16 ColorPaletteId = 0xB001;
	quint16 ColorFilmID = 0xB007;
	quint16 TableId = 0xB002;
	quint16 ThumbnailId = 0xB003;
	quint16 WorkInfoId = 0xB005;
	quint16 DesignDataID = 0xB004;
	quint16 DesignParaId = 0xB006;
	quint16 McColorPaletteId = 0xB008;
	quint16 ReservedId = 0xC001;

	EbdHeader& header = ebdInfo.ebdHeader;

	if (header.DesignNameLength == 0)
	{
		header.DesignName = (quint8*)QString("No Name").toStdString().c_str();
	}

	header.DesignNameLength = header.DesignNameLength;
	header.FileNameLength = header.FileNameLength;
	header.ThumbNailSize = header.ThumbNailSize;

	header.HeaderSize = (uint)(28 + header.DesignNameLength + header.FileNameLength);
	header.TotalHeaderSize = (uint)(50 + header.DesignNameLength + 
										 header.FileNameLength + 
										 header.ColorPaletteSize + 
										 header.ColorFilmDataSize + 
										 header.CCTableSize + 
										 header.ThumbNailSize + 
										 header.MCColorPaletteDataSize);

	header.StitchCount = ebdInfo.getCountOfData();
	header.DesignDataSize = header.StitchCount * 3;

	QFile ebdFile(_fileName);
	if (!ebdFile.open(QIODevice::WriteOnly))
	{
		_errorString = "Could not write a file.";
		return false;;
	}

	QDataStream stream(&ebdFile);

	ebdFile.seek(0);
	ebdFile.flush();

	#pragma region Design Info ID Required	

	stream.writeRawData((char*)&header.DesignStartID, sizeof(quint16));
	stream.writeRawData((char*)&header.Version, sizeof(quint16));
	stream.writeRawData((char*)&header.HeaderID, sizeof(quint16));
	stream.writeRawData((char*)&header.TotalHeaderSize, sizeof(quint32));
	stream.writeRawData((char*)&header.HeaderSize, sizeof(quint32));
	stream.writeRawData((char*)&header.StitchCount, sizeof(quint32));
	stream.writeRawData((char*)&header.Plus_x, sizeof(qint16));
	stream.writeRawData((char*)&header.Plus_y, sizeof(qint16));
	stream.writeRawData((char*)&header.Minus_x, sizeof(qint16));
	stream.writeRawData((char*)&header.Minus_y, sizeof(qint16));
	stream.writeRawData((char*)&header.Gap_x, sizeof(qint16));
	stream.writeRawData((char*)&header.Gap_y, sizeof(qint16));
	stream.writeRawData((char*)&header.DesignLock, sizeof(quint16));
	stream.writeRawData((char*)&header.ColorChangeNum, sizeof(quint16));
	stream.writeRawData((char*)&header.JumpNum, sizeof(quint32));
	stream.writeRawData((char*)&header.DesignNameLength, sizeof(quint16));
	stream.writeRawData((char*)header.DesignName, header.DesignNameLength);
	stream.writeRawData((char*)&header.FileNameLength, sizeof(quint16));
	stream.writeRawData((char*)header.FileName, header.FileNameLength);

	#pragma endregion 

	#pragma region Color palette table  ID

	if (header.ColorPaletteSize != 0)
	{
		quint32 count = header.ColorPaletteSize / (uint)sizeof(header.ColorPaletteData[0]);

		stream.writeRawData((char*)&ColorPaletteId, sizeof(quint16));
		stream.writeRawData((char*)&header.ColorPaletteSize, sizeof(quint32));

		for (int i = 0; i < count; i++)
		{
			stream.writeRawData((char*)&header.ColorPaletteData[i], sizeof(quint32));
		}
	}

	#pragma endregion

	#pragma region Used sequence of color palette ID

	if (header.ColorFilmDataSize != 0)
	{
		quint32 count = header.ColorFilmDataSize / (uint)sizeof(header.ColorFilmData[0]);

		stream.writeRawData((char*)&ColorFilmID, sizeof(quint16));
		stream.writeRawData((char*)&header.ColorFilmDataSize, sizeof(quint32));

		for (int i = 0; i < count; i++)
		{
			char* sData = Control::instance()->structToByte(header.ColorFilmData[i]);
			stream.writeRawData(sData, sizeof(header.ColorFilmData[0]));
		}
	}

	#pragma endregion

	#pragma region C/C table ID

	if (header.CCTableSize != 0)
	{
		int size = sizeof(header.CCTableData[0]);

		long count = header.CCTableSize / size;

		stream.writeRawData((char*)&header.CCTableID, sizeof(quint16));
		stream.writeRawData((char*)&header.CCTableSize, sizeof(quint32));

		for (long i = 0; i < count; i++)
		{
			quint16* sData = new quint16[4];
			memset(sData, 0, 4);

			sData[0] = header.CCTableData[i].Needle;
			sData[1] = header.CCTableData[i].Group;
			sData[2] = header.CCTableData[i].Height;
			sData[3] = header.CCTableData[i].Option;

			stream.writeRawData((char*)sData, size);

			delete[]sData;
			sData = Q_NULLPTR;
		}
	}

	#pragma endregion

	#pragma region Thumbnail ID Required

	stream.writeRawData((char*)&ThumbnailId, sizeof(quint16));
	stream.writeRawData((char*)&header.ThumbNailSize, sizeof(quint32));
	stream.writeRawData(header.ThumbNailData.constData(), header.ThumbNailSize);

	#pragma endregion

	#pragma region Work Info ID

	if ((header.StartPointUse == 1) || (header.FrameHoopUse == 1))
	{
		stream.writeRawData((char*)&WorkInfoId, sizeof(quint16));			   //0xB005
		stream.writeRawData((char*)&header.WorkInfoSize, sizeof(quint32));     //WorkInfoDataSize
		stream.writeRawData((char*)&header.StartPointUse, sizeof(quint16));    //Design Start point use(1) or not(0) 
		stream.writeRawData((char*)&header.XStartGap, sizeof(qint32));         //Design start point distance to frame center point X  
		stream.writeRawData((char*)&header.YStartGap, sizeof(qint32));         //Design start point distance to frame center point Y
		stream.writeRawData((char*)&header.FrameHoopUse, sizeof(quint16));     //Frame & hoop setting use(1) or not(0)
		stream.writeRawData((char*)&header.FrameType, sizeof(quint16));        //Square, round, CAP.....
		stream.writeRawData((char*)&header.HoopType, sizeof(quint16));         //Hoop type(TRF12, SEMI CAP, WIDE CAP, 15X15, 30X30.....)
		stream.writeRawData((char*)&header.WorkAreaWidth, sizeof(quint16));    //Hoop width(1unit mm)
		stream.writeRawData((char*)&header.WorkAreaHeight, sizeof(quint16));   //Hoop height(1unit mm)
		stream.writeRawData((char*)&header.PhysicalXSpace, sizeof(quint16));   //MC max X space(1unit mm)
		stream.writeRawData((char*)&header.PhysicalYSpace, sizeof(quint16));   //MC MAx y space(1unit mm)
		stream.writeRawData((char*)&header.Dummy16_1, sizeof(quint16));        //2byte Reserved
		stream.writeRawData((char*)&header.Dummy16_2, sizeof(quint16));        //2byte Reserved
		stream.writeRawData((char*)&header.Dummy16_3, sizeof(quint16));        //2byte Reserved
		stream.writeRawData((char*)&header.Dummy16_4, sizeof(quint16));        //2byte Reserved
		stream.writeRawData((char*)&header.Dummy32_1, sizeof(quint32));        //4byte Reserved
		stream.writeRawData((char*)&header.Dummy32_2, sizeof(quint32));        //4byte Reserved
		stream.writeRawData((char*)&header.Dummy32_3, sizeof(quint32));        //4byte Reserved
		stream.writeRawData((char*)&header.Dummy32_4, sizeof(quint32));        //4byte Reserved
	}

	#pragma endregion

	#pragma region Design Modify parameter

	if (header.DesignModifyUse == 1)
	{
		stream.writeRawData((char*)&DesignParaId, sizeof(quint16));
		stream.writeRawData((char*)&header.DesignParaSize, sizeof(quint32));
		stream.writeRawData((char*)&header.DesignModifyUse, sizeof(quint16));
		stream.writeRawData((char*)&header.Mirror, sizeof(quint16));
		stream.writeRawData((char*)&header.XScale, sizeof(quint16));
		stream.writeRawData((char*)&header.YScale, sizeof(quint16));
		stream.writeRawData((char*)&header.Angle, sizeof(quint16));
		stream.writeRawData((char*)&header.XSatin, sizeof(qint16));
		stream.writeRawData((char*)&header.YSatin, sizeof(qint16));
		stream.writeRawData((char*)&header.StartStitch, sizeof(quint32));
		stream.writeRawData((char*)&header.StartEndFiltering, sizeof(quint16));
		stream.writeRawData((char*)&header.Dummy_16_5, sizeof(quint16));
		stream.writeRawData((char*)&header.Dummy_16_6, sizeof(quint16));
		stream.writeRawData((char*)&header.Dummy_16_7, sizeof(quint16));
		stream.writeRawData((char*)&header.Dummy_16_8, sizeof(quint16));
		stream.writeRawData((char*)&header.Dummy_32_5, sizeof(quint32));
		stream.writeRawData((char*)&header.Dummy_32_6, sizeof(quint32));
		stream.writeRawData((char*)&header.Dummy_32_7, sizeof(quint32));
		stream.writeRawData((char*)&header.Dummy_32_8, sizeof(quint32));
	}

	#pragma endregion

	#pragma region Machine needle color palette ID

	if (header.MCColorPaletteDataSize != 0)
	{
		quint32 count = header.MCColorPaletteDataSize / (uint)sizeof(header.MCColorPaletteData[0]);

		stream.writeRawData((char*)&McColorPaletteId, sizeof(quint16));
		stream.writeRawData((char*)&header.MCColorPaletteDataSize, sizeof(quint32));

		for (int i = 0; i < count; i++)
		{
			stream.writeRawData((char*)&header.MCColorPaletteData[i], sizeof(quint32));
		}
	}

	#pragma endregion

	stream.writeRawData((char*)&DesignDataID, sizeof(quint16));
	stream.writeRawData((char*)&header.DesignDataSize, sizeof(quint32));

	#pragma region Design Data ID Required

	QList<LinePoint> list = getList(ebdInfo);

	int dCount = list.count() * 3;
	char* data = new char[dCount];
	memset(data, 0, dCount);

	for (int i = 0; i < list.count(); i++)
	{
		const LinePoint& lPoint = list[i];

		data[i * 3] = (char)qRound(list[i].realPoint.x());
		data[(i * 3) + 1] = (char)qRound(list[i].realPoint.y());
		data[(i * 3) + 2] = (char)list[i].type;
	}

	stream.writeRawData((char*)data, dCount);
	ebdFile.close();

	#pragma endregion

	return true;
}