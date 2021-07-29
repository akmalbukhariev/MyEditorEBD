#pragma once

#include "IReadFile.h"

class LIBMYEDITOREBD_EXPORT ReadTbfFile : public IReadFile
{
	Q_OBJECT

public:
	ReadTbfFile(const QString& fileName, QObject* parent = Q_NULLPTR);
	~ReadTbfFile();

	/*Read a file.*/
	bool read(EbdFileInfo& ebdFile, bool readThumbnail);
};
