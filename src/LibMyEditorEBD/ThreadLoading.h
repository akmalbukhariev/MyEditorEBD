#pragma once

#include <QThread>
#include <QDialog>

#include "CommonDef.h"

class LIBMYEDITOREBD_EXPORT ThreadLoading : public QThread
{
	Q_OBJECT

public:
	ThreadLoading(QDialog* dialog, QObject *parent = Q_NULLPTR);
	~ThreadLoading();

protected:

	void run() override;

private:

	QDialog* _dialog;
};
