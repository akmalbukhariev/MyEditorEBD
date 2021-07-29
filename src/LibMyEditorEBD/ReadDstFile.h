#pragma once

#include "IReadFile.h"

class LIBMYEDITOREBD_EXPORT ReadDstFile : public IReadFile
{
	Q_OBJECT

public:
	ReadDstFile(const QString& fileName, QObject* parent = Q_NULLPTR);
	~ReadDstFile();

	/*Read a file.*/
	bool read(EbdFileInfo& ebdFile, bool readThumbnail);
};
