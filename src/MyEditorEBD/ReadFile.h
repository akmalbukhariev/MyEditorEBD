#pragma once

#include <qmath.h>
#include <QObject>
#include <QFileInfo>
#include <QDataStream> 

#include "Control.h"
#include "CalcPoint.h"
#include "CommonDef.h"

using namespace CommonDef;

class ReadFile : public QObject
{
	Q_OBJECT

public:
	 
	ReadFile(const QString& fileName, QObject *parent = Q_NULLPTR);
	ReadFile() {};
	~ReadFile();
	 
	ReadFile& operator=(const ReadFile& other)
	{
		_suffix = other._suffix;
		_fileName = other._fileName;
		return *this;
	}

	/*Read a file.*/
	virtual bool read(EbdFileInfo& ebdFile, bool readThumbnail);

	/*Get an error.*/
	const QString& errorString() const
	{
		return _errorString;
	}

	/*Remove special character from string.*/
	void getRealString(QString& strText);
  
	static int decodeDstDx(char b0, char b1, char b2);
	static int decodeDstDy(char b0, char b1, char b2);

	static char decodeDstFunction(char b2, bool& sequin);

	static int getBit(char b, int bitNumber)
	{
		return (b & (1 << bitNumber)) != 0 ? 1 : 0;
	}
	   
protected:

	/*Check if files is wrong.*/
	bool checkFile();

	/*Get default color*/
	QColor getDefaultColor();

protected:

	int _defaultColorCount;

	FileSuffix _suffix;
	QString _fileName;

	QString _errorString;

	CalcPoint _calcPoint;
};
