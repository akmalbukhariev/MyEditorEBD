#include "ControlThread.h"

ControlThread::ControlThread( QObject* parent )
	: QObject( parent )
{
	_completeOneByOne = false;
	_maxThreadCount = QThread::idealThreadCount();

	initialize();
}

ControlThread::~ControlThread()
{

}

void ControlThread::initialize()
{
	_numThCount = 0;
	_finishThCount = 0;
	_finishPartThCount = 0;
}

void ControlThread::setThreadCount( int mCount )
{
	initialize();
	_numThCount = mCount;
	_runThList.clear();
}

void ControlThread::append( QThread* rThread )
{
	if( !rThread ) return;
	_runThList.append( rThread );
}

void ControlThread::startWorking()
{
	if( _numThCount == 0 )
	{
		initialize();
		_numThCount = _maxThreadCount;
	}

	int thCount = getWorkersCount( _runThList );
	runWorkers( _runThList, thCount );
}

bool ControlThread::isThreadBusy()
{
	bool busy = true;
	if( _numThCount <= _maxThreadCount )
	{
		if( _finishPartThCount == _numThCount )
		{
			busy = false;
			_finishPartThCount = 0;
		}
	}
	else 
	{
		if( _finishPartThCount == _maxThreadCount )
		{
			busy = false;
			_finishPartThCount = 0;
		}
	}

	return busy;
}

QList< QThread* > ControlThread::getWorkers()
{
	QList< QThread* > notWorkingList;

	for( int i = 0; i < _runThList.count(); i++ )
	{
		QThread* wThread = _runThList[ i ];

		if(wThread != Q_NULLPTR && !wThread->isFinished() && !wThread->isRunning() )
		{
			notWorkingList.append( wThread );
		}
	}

	return notWorkingList;
}

int ControlThread::getWorkersCount( QList< QThread* > wList )
{
	int thCount = 0;

	if( _maxThreadCount >= _numThCount )
	{
		thCount = ( _numThCount >= wList.count() ) ? wList.count() : _numThCount;
	}
	else
	{
		thCount = ( _maxThreadCount >= wList.count() ) ? wList.count() : _maxThreadCount;
	}

	return thCount;
}

void ControlThread::runWorkers( QList< QThread* > wList, int wCount )
{
	for( int i = 0; i < wCount; i++ )
	{
		connect( wList[ i ], SIGNAL( finished() ), this, SLOT( slotFinishedThread() ) );
		wList[ i ]->start();
	}
}

void ControlThread::slotFinishedThread()
{
	_finishThCount++;
	_finishPartThCount++;

	if( _runThList.count() == _finishThCount )
	{
		if (_completeOneByOne)
		{
			QThread* th = (QThread*)sender();
			emit sigFinished(th);
		}
		else emit sigFinishedAll();

		return;
	}

	if (_completeOneByOne)
	{
		QThread* th = (QThread*)sender();
		emit sigFinished(th);
	}

	if( isThreadBusy() ) return;

	QList< QThread* > workersList = getWorkers();

	int thCount = getWorkersCount( workersList );
	runWorkers( workersList, thCount );
}

int ControlThread::getMaxThreadCount()
{
	return _maxThreadCount;
}