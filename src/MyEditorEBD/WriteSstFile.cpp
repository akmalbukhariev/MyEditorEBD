#include "WriteSstFile.h"

WriteSstFile::WriteSstFile(const QString& fileName, QObject *parent)
	: WriteFile(fileName, parent)
{
	_suffix = FileSuffix::Sst;
}

WriteSstFile::~WriteSstFile()
{
}

bool WriteSstFile::write(EbdFileInfo& ebdInfo)
{
	EbdHeader& header = ebdInfo.ebdHeader;

	QFile ebdFile(_fileName);
	if (!ebdFile.open(QIODevice::WriteOnly))
	{
		_errorString = "Could not write a file.";
		return false;
	}
	
	QDataStream stream(&ebdFile);

	QList<LinePoint> list = getList(ebdInfo);

	qint16 plusXMinusX = header.Plus_x + qAbs(header.Minus_x);
	qint16 plusYMinusY = header.Plus_y + qAbs(header.Minus_y);

	stream.writeRawData(QString(ebdInfo.getCountOfData()).toStdString().data(), sizeof(qint32));
	stream.writeRawData((char*)&plusXMinusX, sizeof(qint16));
	stream.writeRawData((char*)&plusYMinusY, sizeof(qint16));
	stream.writeRawData((char*)&header.ColorChangeNum, sizeof(quint16));
	stream.writeRawData((char*)&header.JumpNum, sizeof(quint16));

	uchar* designName = new uchar[9];
	memset(designName, 0, 9);
	int length = 8 < QString((char*)header.DesignName).length() ? 8 : QString((char*)header.DesignName).length();
	memcpy(designName, header.DesignName, length);
	stream.writeRawData((char*)designName, length);

	int d32 = 0;
	uchar d1 = 0;
	stream.writeRawData((char*)&d32, sizeof(quint32));
	stream.writeRawData((char*)&d1, sizeof(uchar));

	uchar* repeat = new uchar[134];
	memset(repeat, 0, 134);
	stream.writeRawData((char*)repeat, 134);
	
	int dCount = list.count() * 3;
	char* data = new char[dCount];
	memset(data, 0, dCount);

	for (int i = 0; i < list.count(); i++)
	{
		const LinePoint& lPoint = list[i];

		data[i * 3] = (char)qAbs(lPoint.realPoint.x());
		data[i * 3 + 1] = (char)qAbs(lPoint.realPoint.y());
		data[i * 3 + 2] = (char)(lPoint.type & STITCH::FUNCTION_FILTER);

		switch (data[i * 3 + 2])
		{
			default:
			case STITCH::NORMAL_CODE_SLOW:
				data[i * 3 + 2] = STITCH::NORMAL_CODE;
				break;
			case STITCH::NORMAL_CODE:
			case STITCH::CC_CODE:
			case STITCH::JUMP_CODE:
			case STITCH::END_CODE:
			case STITCH::SQSTART_CODE:
			case STITCH::SQEND_CODE:
				break;
			case STITCH::STOP_CODE://2019.4.23 osi modify, SST format Stop code is continues 2 CC code  
				data[i * 3 + 2] = STITCH::CC_CODE;
				stream.writeRawData((char*)data, dCount);
				data[i * 3] = 0;
				data[(i * 3) + 1] = 0;
				break;
			case STITCH::TRIM_STOP_CODE://2019.4.23 osi modify 
				data[i * 3 + 2] = STITCH::JUMP_CODE;
				stream.writeRawData((char*)data, dCount);
				data[i * 3] = 0;
				data[(i * 3) + 1] = 0;
				data[i * 3 + 2] = STITCH::JUMP_CODE;
				stream.writeRawData((char*)data, dCount);
				data[i * 3] = 0;
				data[(i * 3) + 1] = 0;
				data[i * 3 + 2] = STITCH::JUMP_CODE;
				stream.writeRawData((char*)data, dCount);

				data[i * 3] = 0;
				data[(i * 3) + 1] = 0;
				data[i * 3 + 2] = STITCH::CC_CODE;
				stream.writeRawData((char*)data, dCount);
				data[i * 3] = 0;
				data[(i * 3) + 1] = 0;
				data[i * 3 + 2] = STITCH::CC_CODE;
				//continue;
				break;
			case STITCH::FRONTSQ_CODE:
			case STITCH::REARSQ_CODE:
			case STITCH::ALLSQ_CODE:
			case STITCH::SEQUIN_CODE:
				data[i * 3 + 2] = STITCH::JUMP_CODE;
				break;
		}

		if (data[i * 3 + 2] != STITCH::END_CODE)
		{
			if (lPoint.realPoint.x() > 0)
				data[i * 3 + 2] |= 0x80;
			else
				data[i * 3 + 2] |= 0x40;

			if (lPoint.realPoint.y() < 0)
				data[i * 3 + 2] |= 0x20;
			else
				data[i * 3 + 2] |= 0x10;
		}
	}

	stream.writeRawData(data, dCount);

	ebdFile.close();

	return true;
}