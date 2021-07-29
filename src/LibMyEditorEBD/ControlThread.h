#ifndef CONTROLTHREAD_H
#define CONTROLTHREAD_H

#include <QObject>
#include <QThread>

#include "CommonDef.h"

class LIBMYEDITOREBD_EXPORT ControlThread : public QObject
{
	Q_OBJECT

public:
	explicit ControlThread( QObject *parent = 0 );
	~ControlThread();

	//Initialize all variable.
	void initialize();

	//Complete a thread and send it.
	void completeOneThread(bool yes)
	{
		_completeOneByOne = yes;
	}

	/*Set a thread count.
	The default maxThreadCount is done 
	querying the number of processor cores.*/
	void setThreadCount( int mCount );

	//Append all threads.
	void append( QThread* rThread );

	//Start to work.
	void startWorking();

	//Get a max thread count.
	int getMaxThreadCount();

	//Collect the thread which is able to work.
	QList< QThread* > getWorkers();

	QList<QThread*>& runThList()
	{
		return _runThList;
	}

signals:

	//Send a signal when all threads are finsihed.
	void sigFinishedAll();

	//Send a signal when a thread is finsihed.
	void sigFinished(QThread* thread);

private:

	//Start thread.
	void runWorkers( QList< QThread* > wList, int wCount );

	//Get threads count which are able to work.
	int getWorkersCount( QList< QThread* > wList );

	//Check if threads are busy.
	bool isThreadBusy();

private slots:

	//Finished thread.
	void slotFinishedThread();
	 
private:
	
	bool _completeOneByOne;

	int _maxThreadCount;	//! This is done querying the number of processor cores

	int _numThCount;		//! Count of thread which user wants.    
	int _finishThCount;		//! Count of completed thread.
	int _finishPartThCount;	//! Count of part of thread list.

	QList< QThread* > _runThList; //! All thread list.
};

#endif // CONTROLTHREAD_H
