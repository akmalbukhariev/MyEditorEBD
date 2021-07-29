#pragma once

#include <QPointer>
#include <QPushBUtton>
#include <QtWidgets/QMainWindow>

#include "Control.h"
#include "ColorMenu.h"
#include "CCTableDialog.h"
#include "ui_MyEditorEBD.h"

class MyEditorEBD : public QMainWindow
{
	Q_OBJECT

public:
	MyEditorEBD(QWidget* parent = Q_NULLPTR);

	void runBySwns(const QString& fileName);

private:

	//Initialize UI
	void initUI();

	//Inititalize events.
	void initConnections();
  
	//Initialize form thema
	void initFormThema();

	void closeEvent(QCloseEvent* event);

private slots:
	void slotSelectFile();

	void slotSaveFile();

	void slotOpenCCTableDialog();

	//Click mouse tool bar.
	void slotMouseToolBar();

	void slotMenuWindow();

	void slotAboutDialog();
	  
	void slotSubWindowActivated(QMdiSubWindow* window);

private:
	Ui::MyEditorEBDClass ui;

	bool _closed;
	QString _strFile;

	ColorMenu* _colorMenu;
	QPointer<WidgetWokrDesign> _obj;
};
