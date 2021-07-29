#pragma once

#include <QDialog>

#include "WidgetSewing.h"
#include "ControlThread.h"
#include "MakeDesignThread.h"
#include "ui_PreviewDialog.h"

class PreviewDialog : public QDialog
{
	Q_OBJECT

public:
	PreviewDialog(QWidget* parent = Q_NULLPTR);
	~PreviewDialog();

	QString selectedFile()
	{
		return _selectedFile;
	}

	QIcon selectedIcon()
	{
		return _selectedIcon;
	}

private:
	void initDialog();
	void initConnection();
	void initControlThread();

	void makeThumbNail(MakeDesignThread* th);

private slots:
	void slotLinEedit();
	void slotThFinished(QThread* thread);
	void slotSelectedFile(const QString& strFile, const QIcon& icon);
	void slotSelectedFiles(const QString& path, const QStringList& files);

private:
	Ui::PreviewDialog ui;
	
	int _filesCount;
	int _finishedThreadCount;
	int _finishedSuccessThreadCount;

	QIcon _selectedIcon;
	QString _selectedFile;

	ControlThread* _poolThread;
};
