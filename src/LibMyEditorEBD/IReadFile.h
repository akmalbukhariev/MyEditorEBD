#pragma once

#include <qmath.h>
#include <QObject>
#include <QFileInfo>
#include <QDataStream> 

#include "Control.h"
#include "CalcPoint.h"
#include "CommonDef.h"

using namespace CommonDef;

class LIBMYEDITOREBD_EXPORT IReadFile : public QObject
{
	Q_OBJECT

public:
	 
	IReadFile(const QString& fileName, QObject *parent = Q_NULLPTR);
	IReadFile() {};
	~IReadFile();
	 
	IReadFile& operator=(const IReadFile& other)
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
 
	static FileSuffix fileSuffix(const QString& strFile);

	static int decodeDstDx(char b0, char b1, char b2);
	static int decodeDstDy(char b0, char b1, char b2);

	static char decodeDstFunction(char b2, bool& sequin);

	static int getBit(char b, int bitNumber)
	{
		return (b & (1 << bitNumber)) != 0 ? 1 : 0;
	}

	template<typename T>
	char* structToByte(T t)
	{
		return static_cast<char*>(static_cast<void*>(&t));
	}

	template<typename T>
	T byteToStruct(char* data, T t)
	{
		return *(T*)((void*)data);
	}

public:

	FileSuffix _suffix;
	QString _fileName;

protected:

	/*Check if files is wrong.*/
	bool checkFile();

	/*Get default color*/
	QColor getDefaultColor();

protected:

	int _defaultColorCount;

	QString _errorString;

	CalcPoint _calcPoint;
};
