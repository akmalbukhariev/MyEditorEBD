#pragma once

#include <QtWidgets/QMainWindow>

#include "EBDInfoModel.h"
#include "ControlThread.h"
#include "MakeDesignThread.h"
#include "ui_MyDesignEditorEBD.h"

class MyDesignEditorEBD : public QMainWindow
{
	Q_OBJECT

public:
	MyDesignEditorEBD(QWidget* parent = Q_NULLPTR);

private:
	void initModel();
	void initWindow();
	void initFormThema();
	void initConnection();
	void initControlThread();

	void makeThumbNail(MakeDesignThread* th);

private slots:
	void slotLinEedit();
	void slotThFinished(QThread* thread);
	void slotClickedFile(const EbdFileInfo& ebdInfo);
	void slotDoubleClickedFile(const QString& strFile, const QIcon& icon);
	void slotSelectedFiles(const QString& path, const QStringList& files);

	void slotSelectedRepeat(const EbdFileInfo& ebdInfo);
	void slotSelectedFiltering(const EbdFileInfo& ebdInfo);
	void slotSelectedStitEdit(const EbdFileInfo& ebdInfo);
	void slotSelectedStitchDivide(const EbdFileInfo& ebdInfo);

private:
	Ui::MyDesignEditorEBDClass ui;

	int _filesCount;
	int _finishedThreadCount;
	int _finishedSuccessThreadCount;

	QString _selectedFile;

	EBDInfoModel* _tModel;
	ControlThread* _poolThread;
};
