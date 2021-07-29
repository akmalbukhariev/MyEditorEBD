#pragma once

#include "IReadFile.h"

class LIBMYEDITOREBD_EXPORT ReadSstFile : public IReadFile
{
	Q_OBJECT

public:
	ReadSstFile(const QString& fileName, QObject* parent = Q_NULLPTR);
	~ReadSstFile();

	/*Read a file.*/
	bool read(EbdFileInfo& ebdFile, bool readThumbnail);
};
