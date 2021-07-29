 
#include "MakeDesignThread.h"

#include <QImage>
#include <QDataStream>

MakeDesignThread::MakeDesignThread(const QString& strFile, QObject *parent)
	:_strFile(strFile), QThread(parent)
{
	_readFile = Q_NULLPTR;

	_hasError = "";
	_ebdInfo.strFile = strFile;
}

MakeDesignThread::~MakeDesignThread()
{
	if (_readFile != Q_NULLPTR)
	{
		delete _readFile;
		_readFile = Q_NULLPTR;
	} 
}

void MakeDesignThread::run()
{
	_hasError = false;

	_suffix = Control::instance()->fileSuffix(_strFile);
	switch (_suffix)
	{
		case Sst: _readFile = new ReadSstFile(_strFile); break;
		case Ebd: _readFile = new ReadEbdFile(_strFile); break;
		case Dst: _readFile = new ReadDstFile(_strFile); break;
		case Tbf: _readFile = new ReadTbfFile(_strFile); break;
		default: break;
	}

	if (_readFile != Q_NULLPTR)
	{
		_hasError = !_readFile->read(_ebdInfo, true);
		_errorString = _readFile->errorString();
	}
} 