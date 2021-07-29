#pragma once

#include <WriteFile.h>

class WriteSstFile : public WriteFile
{
	Q_OBJECT

public:
	WriteSstFile(const QString& fileName, QObject * parent = Q_NULLPTR);
	~WriteSstFile();

	/*Write a file.*/
	bool write(EbdFileInfo& ebdInfo);
};
