#pragma once

#include <QFile>
#include <QObject>

#include "Control.h"
#include "CommonDef.h"

using namespace CommonDef;

class WriteFile : public QObject
{
	Q_OBJECT

public:
	WriteFile(const QString& fileName, QObject* parent = Q_NULLPTR);
	WriteFile() {}
	~WriteFile();

	/*Write a file.*/
	virtual bool write(EbdFileInfo& ebdInfo);

	/*Get an error.*/
	const QString& errorString() const
	{
		return _errorString;
	}

protected:
	QList<LinePoint> getList(const EbdFileInfo& ebdInfo);

	uchar* encodeDst(char sx, char sy, uchar fn);

	int ConvertData[122][5] =
	{
		{    0,    0,    0,    0,    0},	//    0
		{    1,    0,    0,    0,    0},	//    1
		{    3,   -1,    0,    0,    0},	//    2
		{    3,    0,    0,    0,    0},	//    3
		{    3,    0,    0,    0,    1},	//    4
		{    9,    0,    0,   -1,   -3},	//    5
		{    9,    0,    0,    0,   -3},	//    6
		{    9,    0,    0,    1,   -3},	//    7
		{    9,    0,    0,    0,   -1},	//    8
		{    9,    0,    0,    0,    0},	//    9
		{    9,    0,    0,    0,    1},	//   10
		{    9,    0,    0,    3,   -1},	//   11
		{    9,    0,    0,    0,    3},	//   12
		{    9,    0,    0,    3,    1},	//   13
		{   27,    0,   -1,   -3,   -9},	//   14
		{   27,    0,    0,   -3,   -9},	//   15
		{   27,    0,    1,   -3,   -9},	//   16
		{   27,    0,    0,   -1,   -9},	//   17
		{   27,    0,    0,    0,   -9},	//   18
		{   27,    0,    0,    1,   -9},	//   19
		{   27,    0,    3,   -1,   -9},	//   20
		{   27,    0,    0,    3,   -9},	//   21
		{   27,    0,    3,    1,   -9},	//   22
		{   27,    0,    0,   -1,   -3},	//   23
		{   27,    0,    0,    0,   -3},	//   24
		{   27,    0,    0,    1,   -3},	//   25
		{   27,    0,    0,    0,   -1},	//   26
		{   27,    0,    0,    0,    0},	//   27
		{   27,    0,    0,    0,    1},	//   28
		{   27,    0,    0,    3,   -1},	//   29
		{   27,    0,    0,    0,    3},	//   30
		{   27,    0,    0,    3,    1},	//   31
		{   27,    0,    9,   -1,   -3},	//   32
		{   27,    0,    0,    9,   -3},	//   33
		{   27,    0,    9,    1,   -3},	//   34
		{   27,    0,    0,    9,   -1},	//   35
		{   27,    0,    0,    0,    9},	//   36
		{   27,    0,    0,    9,    1},	//   37
		{   27,    0,    9,    3,   -1},	//   38
		{   27,    0,    0,    9,    3},	//   39
		{   27,    0,    9,    3,    1},	//   40
		{   81,   -1,   -3,   -9,  -27},	//   41
		{   81,    0,   -3,   -9,  -27},	//   42
		{   81,    1,   -3,   -9,  -27},	//   43
		{   81,    0,   -1,   -9,  -27},	//   44
		{   81,    0,    0,   -9,  -27},	//   45
		{   81,    0,    1,   -9,  -27},	//   46
		{   81,    3,   -1,   -9,  -27},	//   47
		{   81,    0,    3,   -9,  -27},	//   48
		{   81,    3,    1,   -9,  -27},	//   49
		{   81,    0,   -1,   -3,  -27},	//   50
		{   81,    0,    0,   -3,  -27},	//   51
		{   81,    0,    1,   -3,  -27},	//   52
		{   81,    0,    0,   -1,  -27},	//   53
		{   81,    0,    0,    0,  -27},	//   54
		{   81,    0,    0,    1,  -27},	//   55
		{   81,    0,    3,   -1,  -27},	//   56
		{   81,    0,    0,    3,  -27},	//   57
		{   81,    0,    3,    1,  -27},	//   58
		{   81,    9,   -1,   -3,  -27},	//   59
		{   81,    0,    9,   -3,  -27},	//   60
		{   81,    9,    1,   -3,  -27},	//   61
		{   81,    0,    9,   -1,  -27},	//   62
		{   81,    0,    0,    9,  -27},	//   63
		{   81,    0,    9,    1,  -27},	//   64
		{   81,    9,    3,   -1,  -27},	//   65
		{   81,    0,    9,    3,  -27},	//   66
		{   81,    9,    3,    1,  -27},	//   67
		{   81,    0,   -1,   -3,   -9},	//   68
		{   81,    0,    0,   -3,   -9},	//   69
		{   81,    0,    1,   -3,   -9},	//   70
		{   81,    0,    0,   -1,   -9},	//   71
		{   81,    0,    0,    0,   -9},	//   72
		{   81,    0,    0,    1,   -9},	//   73
		{   81,    0,    3,   -1,   -9},	//   74
		{   81,    0,    0,    3,   -9},	//   75
		{   81,    0,    3,    1,   -9},	//   76
		{   81,    0,    0,   -1,   -3},	//   77
		{   81,    0,    0,    0,   -3},	//   78
		{   81,    0,    0,    1,   -3},	//   79
		{   81,    0,    0,    0,   -1},	//   80
		{   81,    0,    0,    0,    0},	//   81
		{   81,    0,    0,    0,    1},	//   82
		{   81,    0,    0,    3,   -1},	//   83
		{   81,    0,    0,    0,    3},	//   84
		{   81,    0,    0,    3,    1},	//   85
		{   81,    0,    9,   -1,   -3},	//   86
		{   81,    0,    0,    9,   -3},	//   87
		{   81,    0,    9,    1,   -3},	//   88
		{   81,    0,    0,    9,   -1},	//   89
		{   81,    0,    0,    0,    9},	//   90
		{   81,    0,    0,    9,    1},	//   91
		{   81,    0,    9,    3,   -1},	//   92
		{   81,    0,    0,    9,    3},	//   93
		{   81,    0,    9,    3,    1},	//   94
		{   81,   27,   -1,   -3,   -9},	//   95
		{   81,    0,   27,   -3,   -9},	//   96
		{   81,   27,    1,   -3,   -9},	//   97
		{   81,    0,   27,   -1,   -9},	//   98
		{   81,    0,    0,   27,   -9},	//   99
		{   81,    0,   27,    1,   -9},	//  100
		{   81,   27,    3,   -1,   -9},	//  101
		{   81,    0,   27,    3,   -9},	//  102
		{   81,   27,    3,    1,   -9},	//  103
		{   81,    0,   27,   -1,   -3},	//  104
		{   81,    0,    0,   27,   -3},	//  105
		{   81,    0,   27,    1,   -3},	//  106
		{   81,    0,    0,   27,   -1},	//  107
		{   81,    0,    0,    0,   27},	//  108
		{   81,    0,    0,   27,    1},	//  109
		{   81,    0,   27,    3,   -1},	//  110
		{   81,    0,    0,   27,    3},	//  111
		{   81,    0,   27,    3,    1},	//  112
		{   81,   27,    9,   -1,   -3},	//  113
		{   81,    0,   27,    9,   -3},	//  114
		{   81,   27,    9,    1,   -3},	//  115
		{   81,    0,   27,    9,   -1},	//  116
		{   81,    0,    0,   27,    9},	//  117
		{   81,    0,   27,    9,    1},	//  118
		{   81,   27,    9,    3,   -1},	//  119
		{   81,    0,   27,    9,    3},	//  120
		{   81,   27,    9,    3,    1} 	//  121
	};

protected:

	FileSuffix _suffix;
	QString _fileName;
	QString _errorString;
};