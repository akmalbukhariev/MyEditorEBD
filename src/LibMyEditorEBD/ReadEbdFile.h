#pragma once

#include "IReadFile.h"

class LIBMYEDITOREBD_EXPORT ReadEbdFile : public IReadFile
{
	Q_OBJECT

public:
	ReadEbdFile(const QString& fileName, QObject* parent = Q_NULLPTR);
	~ReadEbdFile();

	/*Read a file.*/
	bool read(EbdFileInfo& ebdFile, bool readThumbnail);

private:
	void readAllData(QDataStream& stream, int length, EbdFileInfo& ebdInfo);
};
