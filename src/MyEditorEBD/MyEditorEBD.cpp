#include "MakeDesign.h"
#include "AboutDialog.h"
#include "MyEditorEBD.h"
#include "PreviewDialog.h"

#include <QSettings>
#include <QMessageBox>
#include <QFileDialog> 
#include <QCloseEvent>
#include <QMdiSubWindow>
#include <QStyleFactory>

MyEditorEBD::MyEditorEBD(QWidget* parent)
	: QMainWindow(parent)
{
	_closed = false;

	ui.setupUi(this);
	initUI();
	initConnections();
	//initFormThema();
	showMaximized();
}

void MyEditorEBD::runBySwns(const QString& fileName)
{
	qDebug() << "Open file ";
	qDebug() << fileName;

	ui.designContainer->addWindow(fileName);
	if (!ui.designContainer->hasError())
	{
		FileSuffix suffix = Control::instance()->fileSuffix(fileName);

		ReadFile* readFile;
		switch (suffix)
		{
		case CommonDef::Sst:
			readFile = new ReadSstFile(fileName);
			break;
		case CommonDef::Dst:
			readFile = new ReadDstFile(fileName);
			break;
		case CommonDef::Tbf:
			readFile = new ReadTbfFile(fileName);
			break;
		default:
			break;
		}

		EbdFileInfo ebdFileInfo;
		if (readFile->read(ebdFileInfo, true))
		{
			MakeDesign thumbNail;
			thumbNail.makeThumbnail(&ebdFileInfo);
		}

		ui.wdDesign->addDesign(QIcon(ebdFileInfo.thumbNail), fileName);
	}
}

void MyEditorEBD::initUI()
{
	ui.actionScale->setVisible(false);
	ui.actionRotate->setVisible(false);
	ui.actionEditStitches->setVisible(false);

	_colorMenu = new ColorMenu(ui.colorToolBar);

	//ui.designContainer->setStitchColor(_colorMenu->getColorList());
	//ui.designContainer->addWindow("D:/Storage Card/WcEmb/TDesign/1576581840.ebd");
	//ui.designContainer->addWindow("D:/Hard Disk/TestDesign/1576581840.EBD");
	//ui.designContainer->addWindow("D:/Hard Disk/Wilcom EBD 2-4 Files/Custom Letters.EBD");
	//ui.designContainer->addWindow("D:/Hard Disk/Wilcom EBD 2-4 Files/e4-1028.EBD");
	//ui.designContainer->addWindow("D:/Hard Disk/Wilcom EBD 2-4 Files/e4-1035.EBD");
	//ui.designContainer->addWindow("D:/Hard Disk/nike.SST");
	//ui.designContainer->addWindow("D:/Hard Disk/SWF005_000.DST");

	//ui.dkPoint->setVisible(false);
	//ui.dkHeader->setVisible(false);

	/*ui.dkCCTable->setAllowedAreas(Qt::DockWidgetArea::LeftDockWidgetArea);
	ui.dkColorFilm->setAllowedAreas(Qt::DockWidgetArea::LeftDockWidgetArea);
	ui.dkPoint->setAllowedAreas(Qt::DockWidgetArea::RightDockWidgetArea);*/

	ui.dkCCTable->setVisible(false);
	ui.dkImageMap->setVisible(false);
	ui.dkSequenceViewer->setVisible(false);
}

void MyEditorEBD::initConnections()
{
	connect(ui.actionExit, &QAction::triggered, this, &QWidget::close);
	connect(ui.actionOpen_File, &QAction::triggered, this, &MyEditorEBD::slotSelectFile);
	connect(ui.actionSave_File, &QAction::triggered, this, &MyEditorEBD::slotSaveFile);
	connect(ui.actionCCTable, &QAction::triggered, this, &MyEditorEBD::slotOpenCCTableDialog);

	connect(ui.actionAxis, &QAction::triggered, this, &MyEditorEBD::slotMouseToolBar);
	connect(ui.actionPointing, &QAction::triggered, this, &MyEditorEBD::slotMouseToolBar);
	connect(ui.actionTransform, &QAction::triggered, this, &MyEditorEBD::slotMouseToolBar);

	connect(ui.actionTile_Window, &QAction::triggered, this, &MyEditorEBD::slotMenuWindow);
	connect(ui.actionCascade_Window, &QAction::triggered, this, &MyEditorEBD::slotMenuWindow);
	connect(ui.actionAbout, &QAction::triggered, this, &MyEditorEBD::slotAboutDialog);
	
	connect(ui.actionDesignGrid, &QAction::triggered, this, &MyEditorEBD::slotMouseToolBar);
	connect(ui.actionEditStitches, &QAction::triggered, this, &MyEditorEBD::slotMouseToolBar);

	connect(Control::instance(), &Control::sigSelectedDesign, ui.designContainer, &DesignContainer::setActiveWindow);
	//connect(Control::instance(), &Control::sigCleanAllModels, this, &MyEditorEBD::slotCloseWorkDesign);

	connect(_colorMenu, &ColorMenu::sigClickButton, ui.wdColorFilm, &WidgetColorFilm::refreshModel);

	//connect(ui.designContainer, &DesignContainer::sigDesignDataChanged, ui.wdDesign, &WidgetDesignNavigator::addItem);
	connect(ui.designContainer, &DesignContainer::sigDesignDataChanged, ui.wdCCTable, &WidgetCCTable::slotWorkDesign);
	connect(ui.designContainer, &DesignContainer::sigDesignDataChanged, ui.wdPoint, &WidgetPointInfo::slotWorkDesign);
	connect(ui.designContainer, &DesignContainer::sigDesignDataChanged, ui.wdPoint, &WidgetPointInfo::slotUpdateScroll);
	connect(ui.designContainer, &DesignContainer::sigDesignDataChanged, ui.wdColorFilm, &WidgetColorFilm::slotWorkDesign);
	connect(ui.designContainer, &DesignContainer::sigDesignDataChanged, ui.wdHeaderInfo, &WidgetHeaderInfo::slotWorkDesign);

	connect(ui.designContainer, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(slotSubWindowActivated(QMdiSubWindow*)));
}

void MyEditorEBD::initFormThema()
{
	qApp->setStyle(QStyleFactory::create("fusion"));

	QPalette palette;
	palette.setColor(QPalette::Text, Qt::white);
	palette.setColor(QPalette::BrightText, Qt::red);
	palette.setColor(QPalette::ButtonText, Qt::white);
	palette.setColor(QPalette::WindowText, Qt::white);
	palette.setColor(QPalette::ToolTipBase, Qt::white);
	palette.setColor(QPalette::ToolTipText, Qt::white);
	palette.setColor(QPalette::Base, QColor(15, 15, 15));
	palette.setColor(QPalette::Button, QColor(53, 53, 53));
	palette.setColor(QPalette::HighlightedText, Qt::black);
	palette.setColor(QPalette::Window, QColor(53, 53, 53));
	palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
	palette.setColor(QPalette::Highlight, QColor(142, 45, 197).lighter());
	qApp->setPalette(palette);
}

void MyEditorEBD::slotSelectFile()
{
	PreviewDialog pDialog;
	pDialog.exec();

	/*QSettings settings("Sunstar", "BinaryFile");
	QString strLastPath = settings.value("LastOpenPath").toString();

	_strFile = QFileDialog::getOpenFileName(this, tr("Open File"), strLastPath, tr("EBD files (*.EBD );; All files( *.* )"));
	settings.setValue("LastOpenPath", QDir(_strFile).absolutePath());*/

	if (pDialog.selectedFile().isEmpty()) return;

	ui.designContainer->addWindow(pDialog.selectedFile());
	if (!ui.designContainer->hasError())
		ui.wdDesign->addDesign(pDialog.selectedIcon(), pDialog.selectedFile());
}

void MyEditorEBD::slotSaveFile()
{
	if (_obj.isNull() == false)
	{
		QString strSelected = QString::null;
		QString strFileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Ebd-File (*.ebd);;All Files (*)"), &strSelected);
		//strFileName = "D:/Hard Disk/yyyyyyyy/test.EBD";
		//strFileName = "D:/Hard Disk/yyyyyyyy/test.DST";
		//strFileName = "D:/Hard Disk/yyyyyyyy/test.SST";
		
		//Control::instance()->showLoading();

		MakeDesign design; 
		if(design.write(_obj.data()->getFileInfo(), strFileName));
		{
			QMessageBox::information(this, "Save file", "Saveing has completed.");
		}

		//Control::instance()->closeLoading();
	}
}

void MyEditorEBD::slotMouseToolBar()
{
	WidgetWokrDesign* wD = ui.designContainer->getActiveDesignWindow();

	if (wD == NULL) return;

	if (sender() == ui.actionTransform)
	{
		wD->setReArrangeObjects(ui.actionTransform->isChecked());
	}
	else if (sender() == ui.actionEditStitches)
	{
		wD->setEditStitches(ui.actionEditStitches->isChecked());
	}
	else if (sender() == ui.actionDesignGrid)
	{
		wD->setGridVisible(ui.actionDesignGrid->isChecked());
	}
	else if (sender() == ui.actionAxis)
	{
		wD->setAxisVisible(ui.actionAxis->isChecked());
	}
	else if (sender() == ui.actionPointing)
	{
		wD->setPointingPoint(ui.actionPointing->isChecked());
	}
}

void MyEditorEBD::slotOpenCCTableDialog()
{	
	if (_obj.isNull()) return;

	try
	{
		CCTableDialog ccDialog(&_obj.data()->getFileInfo());
		ccDialog.exec();
	}
	catch (const std::exception&)
	{
		
	}
}
 
void MyEditorEBD::slotSubWindowActivated(QMdiSubWindow* window)
{
	if (window == NULL) return;

	WidgetWokrDesign* workWidget = qobject_cast<WidgetWokrDesign*>(window->widget());
	_obj = QPointer<WidgetWokrDesign>(workWidget);

	if (workWidget != NULL)
	{
		//ui.wdNavigator->setDesignMap(Control::instance()->getPixmapFromNavigationList(wD->getFileInfo().navigateId));

		_colorMenu->setWorkDesign(workWidget);

		ui.wdPoint->slotWorkDesign(workWidget);
		ui.wdCCTable->slotWorkDesign(workWidget);
		ui.wdColorFilm->slotWorkDesign(workWidget);
		ui.wdHeaderInfo->slotWorkDesign(workWidget);

		ui.wdDesign->selectItemFile(workWidget->getFileInfo().strFile);

		ui.actionAxis->setChecked(workWidget->getVisibleAxis());
		ui.actionDesignGrid->setChecked(workWidget->getVisibleGrid());
		ui.actionEditStitches->setChecked(workWidget->getEditStitches());
		ui.actionTransform->setChecked(workWidget->getReArrangeObjects());
		ui.actionPointing->setChecked(workWidget->getVisiblePointingPoint());
	}
}

void MyEditorEBD::slotMenuWindow()
{
	if (sender() == ui.actionTile_Window)
	{
		ui.designContainer->tileSubWindows();
	}
	else if (sender() == ui.actionCascade_Window)
	{
		ui.designContainer->cascadeSubWindows();
	}
}

void MyEditorEBD::slotAboutDialog()
{
	AboutDialog dialog;
	dialog.exec();
}

void MyEditorEBD::closeEvent(QCloseEvent* event)
{
	_closed = true;
	QMessageBox::StandardButton btn = QMessageBox::question(this, "Exit", "Do you really want to exit?", QMessageBox::Yes | QMessageBox::No);
	switch (btn)
	{
		case QMessageBox::Yes: event->accept(); break;
		case QMessageBox::No: event->ignore(); break;
	}
}