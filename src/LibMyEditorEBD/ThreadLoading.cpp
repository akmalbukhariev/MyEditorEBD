#include "ThreadLoading.h"

#include <QMetaObject>

ThreadLoading::ThreadLoading(QDialog* dialog, QObject *parent)
	: _dialog(dialog), QThread(parent)
{
}

ThreadLoading::~ThreadLoading()
{
}

void ThreadLoading::run()
{
	if (_dialog != Q_NULLPTR)
	{
		QMetaObject::invokeMethod(_dialog, "exec");
	}
}
