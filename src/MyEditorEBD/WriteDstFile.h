#pragma once

#include <WriteFile.h>

class WriteDstFile : public WriteFile
{
	Q_OBJECT

public:
	WriteDstFile(const QString& fileName, QObject * parent = Q_NULLPTR);
	~WriteDstFile();

	/*Write a file.*/
	bool write(EbdFileInfo& ebdInfo);

};
