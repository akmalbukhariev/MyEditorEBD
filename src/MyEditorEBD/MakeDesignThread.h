#pragma once

#include <QIcon>
#include <QThread>

#include "ReadFile.h"
#include "ReadDstFile.h"
#include "ReadEbdFile.h"
#include "ReadSstFile.h"
#include "ReadTbfFile.h"

class MakeDesignThread : public QThread
{
	Q_OBJECT

public:
	MakeDesignThread(const QString& strFile, QObject* parent = Q_NULLPTR);
	~MakeDesignThread();

	bool hasError() const
	{
		return _hasError;
	}

	QString getErrorString() const
	{
		return _errorString;
	}

	FileSuffix getSuffix()
	{
		return _suffix;
	}

	EbdFileInfo& getEbdInfo()
	{
		return _ebdInfo;
	}

	const QString& getFile() const
	{
		return _strFile;
	}

protected:
	void run() override;
	 
private:
	bool _hasError;

	FileSuffix _suffix;

	QString _strFile;
	QString _errorString;

	ReadFile* _readFile;
	EbdFileInfo _ebdInfo;
};
