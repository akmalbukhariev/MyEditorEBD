#include "MyEditorEBD.h"
#include <QtWidgets/QApplication>

#include <QFile>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	 
	/*QFile file("D:/Hard Disk/TestDesign/1576581840.EBD");
	if (!file.open(QIODevice::ReadOnly))
	{
		return false;
	}

	QDataStream stream(&file);
	
	quint16 hData;

	stream.skipRawData(38);
	stream.readRawData((char*)&hData, sizeof(quint16));
	stream.skipRawData(hData);
	stream.readRawData((char*)&hData, sizeof(quint16));
	stream.skipRawData(hData + 2);

	quint32 colorSize;
	stream.readRawData((char*)&colorSize, sizeof(quint32));

	quint32 count = colorSize / 4;
	stream.skipRawData((4 * count) + 2);

	quint32 tableSize;
	stream.readRawData((char*)&tableSize, sizeof(quint32));

	count = tableSize / 8;

	stream.skipRawData(8 * count);
	stream.readRawData((char*)&hData, sizeof(quint16));
	

	quint16 ThumbnailId = 0xB003;

	if (ThumbnailId == hData)
	{
		quint32 thumbNailSize;
		stream.readRawData((char*)&thumbNailSize, sizeof(quint32));
	}*/
	 
	qDebug() << "CCCC " << argc;

	QString strSwnsFile = "";
	for (int i = 1; i < argc; i++)
	{
		strSwnsFile += argv[i];
		//qDebug() << "File Name " << strSwnsFile;
	}

	qDebug() << "File Name " << strSwnsFile;

	MyEditorEBD w;
	if (argc > 1)
	{
		w.runBySwns(strSwnsFile);
	}
	w.show();
	 
	return a.exec();
}
