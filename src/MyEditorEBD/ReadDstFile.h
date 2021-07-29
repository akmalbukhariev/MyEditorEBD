#pragma once

#include "ReadFile.h"

class ReadDstFile : public ReadFile
{
	Q_OBJECT

public:
	ReadDstFile(const QString& fileName, QObject* parent = Q_NULLPTR);
	~ReadDstFile();

	/*Read a file.*/
	bool read(EbdFileInfo& ebdFile, bool readThumbnail);
};
