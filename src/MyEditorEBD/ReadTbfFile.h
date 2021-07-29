#pragma once

#include "ReadFile.h"

class ReadTbfFile : public ReadFile
{
	Q_OBJECT

public:
	ReadTbfFile(const QString& fileName, QObject* parent = Q_NULLPTR);
	~ReadTbfFile();

	/*Read a file.*/
	bool read(EbdFileInfo& ebdFile, bool readThumbnail);
};
