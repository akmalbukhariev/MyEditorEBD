#include "WriteDstFile.h"

WriteDstFile::WriteDstFile(const QString& fileName, QObject *parent)
	: WriteFile(fileName, parent)
{
	_suffix = FileSuffix::Dst;
}

WriteDstFile::~WriteDstFile()
{
}

bool WriteDstFile::write(EbdFileInfo& ebdInfo)
{
	EbdHeader& header = ebdInfo.ebdHeader;

	qint32 d13 = 0x0d;
	qint32 d26 = 0x1a;

	QFile ebdFile(_fileName);
	if (!ebdFile.open(QIODevice::WriteOnly))
	{
		_errorString = "Could not write a file.";
		return false;;
	}

	QDataStream stream(&ebdFile);
	int count = 0x200;
	char* repeat = new char[count];
	memset(repeat, 0x20, count);
	
	ebdFile.seek(0x00);
	QString strText = "LA:";
	stream.writeRawData(strText.toStdString().data(), strText.length());
	int length = 16 < QString((char*)header.DesignName).length() ? 16 : QString((char*)header.DesignName).length();
	stream.writeRawData(QString("No Name").toUtf8().data(), length);

	ebdFile.seek(0x1e);
	stream.writeRawData((char*)&d13, sizeof(qint32));
	strText = "CO:";
	stream.writeRawData(strText.toStdString().data(), strText.length());
	int d = QString(header.ColorChangeNum).length();
	ebdFile.seek(3 - d);
	stream.writeRawData(QString(header.ColorChangeNum).toStdString().data(), sizeof(char));

	ebdFile.seek(0x25);
	stream.writeRawData((char*)&d13, sizeof(qint32));
	strText = "+X:";
	stream.writeRawData(strText.toStdString().data(), strText.length());
	d = QString(header.Plus_x).length();
	ebdFile.seek(5 - d);
	stream.writeRawData(QString(header.Plus_x).toStdString().data(), sizeof(char));

	ebdFile.seek(0x2e);
	stream.writeRawData((char*)&d13, sizeof(qint32));
	strText = "-X:";
	stream.writeRawData(strText.toStdString().data(), strText.length());
	d = QString(header.Minus_x).length();
	ebdFile.seek(5 - d);
	stream.writeRawData(QString(qAbs(header.Minus_x)).toStdString().data(), sizeof(char));

	ebdFile.seek(0x37);
	stream.writeRawData((char*)&d13, sizeof(qint32));
	strText = "+Y:";
	stream.writeRawData(strText.toStdString().data(), strText.length());
	d = QString(header.Plus_y).length();
	ebdFile.seek(5 - d);
	stream.writeRawData(QString(header.Plus_y).toStdString().data(), sizeof(char));

	ebdFile.seek(0x40);
	stream.writeRawData((char*)&d13, sizeof(qint32));
	strText = "-Y:";
	stream.writeRawData(strText.toStdString().data(), strText.length());
	d = QString(header.Minus_y).length();
	ebdFile.seek(5 - d);
	stream.writeRawData(QString(qAbs(header.Minus_y)).toStdString().data(), sizeof(char));
	 
	ebdFile.seek(0x49); 
	stream.writeRawData((char*)&d13, sizeof(qint32));
	strText = "AX:";
	stream.writeRawData(strText.toStdString().data(), strText.length());
	
	ebdFile.seek(0x53);
	stream.writeRawData((char*)&d13, sizeof(qint32));
	strText = "AY:";
	stream.writeRawData(strText.toStdString().data(), strText.length());
		
	ebdFile.seek(0x5d);
	stream.writeRawData((char*)&d13, sizeof(qint32));
	strText = "MX:";
	stream.writeRawData(strText.toStdString().data(), strText.length());
	
	ebdFile.seek(0x67);
	stream.writeRawData((char*)&d13, sizeof(qint32));
	strText = "MY:";
	stream.writeRawData(strText.toStdString().data(), strText.length());
		
	ebdFile.seek(0x71);
	stream.writeRawData((char*)&d13, sizeof(qint32));
	strText = "PD:******";
	stream.writeRawData(strText.toStdString().data(), strText.length());
		
	stream.writeRawData((char*)&d13, sizeof(qint32));
	stream.writeRawData((char*)&d26, sizeof(qint32));

	ebdFile.seek(0x200);

	int stitchCount = 0;
	QList<LinePoint> list = getList(ebdInfo);
	for (int i = 0; i < list.count(); i++)
	{
		const LinePoint& lPoint = list[i];

		char sx = (char)lPoint.realPoint.x();
		char sy = (char)lPoint.realPoint.y();
		char fn = (char)lPoint.type;

		if (qAbs(sx) > 120 || qAbs(sy) > 120)
		{
			sx = (char)(sx / 2);
			sy = (char)(sy / 2);
			stream.writeRawData((char*)encodeDst((char)(sx + (sx % 2)), (char)(sy + (sy % 2)), STITCH::JUMP_CODE), 3);
			stitchCount++;
		}

		stream.writeRawData((char*)encodeDst(sx, sy, fn), sizeof(uchar));
		stitchCount++;

		switch (fn & STITCH::FUNCTION_FILTER)
		{
			case STITCH::REARSQ_CODE:
				stream.writeRawData((char*)encodeDst(0, 0, STITCH::FRONTSQ_CODE), 3);
				break;
			case STITCH::ALLSQ_CODE:
				stream.writeRawData((char*)encodeDst(0, 0, STITCH::FRONTSQ_CODE), 3);
				stream.writeRawData((char*)encodeDst(0, 0, STITCH::FRONTSQ_CODE), 3);
				break;
		}

		ebdFile.seek(0x13);
		stream.writeRawData((char*)&d13, sizeof(qint32));
		strText = "ST:";
		stream.writeRawData(strText.toStdString().data(), strText.length());
		d = QString(stitchCount).length();
		ebdFile.seek(7 - d);
		stream.writeRawData(QString(header.StitchCount).toStdString().data(), QString(header.StitchCount).length());
	}

	ebdFile.close();

	return true;
}
