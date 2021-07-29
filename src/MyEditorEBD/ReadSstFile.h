#pragma once

#include "ReadFile.h"

class ReadSstFile : public ReadFile
{
	Q_OBJECT

public:
	ReadSstFile(const QString& fileName, QObject* parent = Q_NULLPTR);
	~ReadSstFile();

	/*Read a file.*/
	bool read(EbdFileInfo& ebdFile, bool readThumbnail);
};
