#pragma once

#include "WriteFile.h"

class WriteEbdFile : public WriteFile
{
	Q_OBJECT

public:
	WriteEbdFile(const QString& fileName, QObject* parent = Q_NULLPTR);
	~WriteEbdFile();

	/*Write a file.*/
	bool write(EbdFileInfo& ebdFile);
};
