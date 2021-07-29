#include "IReadFile.h"

IReadFile::IReadFile(const QString& fileName, QObject *parent)
	:_fileName(fileName), QObject(parent)
{
	_defaultColorCount = 0;
}

IReadFile::~IReadFile()
{
}

bool IReadFile::checkFile()
{
	QString strSuffix = "";
	switch (_suffix)
	{
		case Sst: strSuffix = "SST"; break;
		case Ebd: strSuffix = "EBD"; break;
		case Dst: strSuffix = "DST"; break;
		case Tbf: strSuffix = "TBF"; break;
		default: break;
	}

	QFileInfo fInfo(_fileName);
	if (fInfo.suffix().toUpper() != strSuffix)
	{
		_errorString = "You have selected wrong file.";
		return false;
	}
	 
	return true;
}

bool IReadFile::read(EbdFileInfo& ebdFile, bool readData)
{
	return true;
}

FileSuffix IReadFile::fileSuffix(const QString& strFile)
{
	FileSuffix suffix = FileSuffix::NoneFile;

	QFileInfo fInfo(strFile);
	if (fInfo.suffix().toUpper() == "SST")
	{
		suffix = FileSuffix::Sst;
	}
	else if (fInfo.suffix().toUpper() == "EBD")
	{
		suffix = FileSuffix::Ebd;
	}
	else if (fInfo.suffix().toUpper() == "DST")
	{
		suffix = FileSuffix::Dst;
	}
	else if (fInfo.suffix().toUpper() == "TBF")
	{
		suffix = FileSuffix::Tbf;
	}

	return suffix;
}

void IReadFile::getRealString(QString& strText)
{
	QRegExp reg(QString::fromUtf8("[`~!@#$%^&*()_â€”+=|:;<>Â«Â»ݕT ݷ,?/{}\'\"\\\[\\\]\\\\]"));
	//"[`~!@�#$%^&*+=|:;<>«»,?/{}\'\"\\\[\\\]\\\\]"));
	//("[-`~!@#$%^&*()_â€”+=|:;<>Â«Â»,.?/{}\'\"\\\[\\\]\\\\]")));

	strText.remove(reg);
}

int IReadFile::decodeDstDx(char b0, char b1, char b2)
{
	int x = 0;

	x += getBit(b2, 2) * (+81);
	x += getBit(b2, 3) * (-81);
	x += getBit(b1, 2) * (+27);
	x += getBit(b1, 3) * (-27);
	x += getBit(b0, 2) * (+9);
	x += getBit(b0, 3) * (-9);
	x += getBit(b1, 0) * (+3);
	x += getBit(b1, 1) * (-3);
	x += getBit(b0, 0) * (+1);
	x += getBit(b0, 1) * (-1);

	return qRound((double)x);
}

int IReadFile::decodeDstDy(char b0, char b1, char b2)
{
	int y = 0;

	y += getBit(b2, 5) * (+81);
	y += getBit(b2, 4) * (-81);
	y += getBit(b1, 5) * (+27);
	y += getBit(b1, 4) * (-27);
	y += getBit(b0, 5) * (+9);
	y += getBit(b0, 4) * (-9);
	y += getBit(b1, 7) * (+3);
	y += getBit(b1, 6) * (-3);
	y += getBit(b0, 7) * (+1);
	y += getBit(b0, 6) * (-1);

	return qRound((double)y);
}

char IReadFile::decodeDstFunction(char b2, bool& sequin)
{
	char b;

	if (b2 == 0xF3)
		return END_CODE;

	switch (b2 & 0xC3) // 0xF3
	{
		case 0x03:
			b = NORMAL_CODE;
			break;
		case 0x83:
			if (sequin == true)
				b = FRONTSQ_CODE;
			else
				b = JUMP_CODE;
			break;
		case 0xC3:
			b = CC_CODE;
			break;
		case 0x43:
			sequin ^= true;
			if (sequin == true)
				b = SQSTART_CODE;
			else
				b = SQEND_CODE;
			break;
		default:
			b = 0xFF;
			break;
	};

	return b;
}

QColor IReadFile::getDefaultColor()
{
	short cMax = 255;
	short cMin = 0;

	int R = qrand() % (cMax - cMin + 1) + cMin;
	int G = qrand() % (cMax - cMin + 1) + cMin;
	int B = qrand() % (cMax - cMin + 1) + cMin;

	return QColor(R, G, B);
}