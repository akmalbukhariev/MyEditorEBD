#include "DrawDesign.h"
#include "DialogRepeat.h"
#include "DialogFiltering.h"
#include "DialogStitchEdit.h"
#include "DialogStitchDivide.h"
#include "MyDesignEditorEBD.h"

#include <QDebug>
#include <QSettings>
#include <QStyleFactory>

MyDesignEditorEBD::MyDesignEditorEBD(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	_tModel = Q_NULLPTR;

	initConnection();
	initControlThread();
	initWindow();
	initModel();
	initFormThema();
}

void MyDesignEditorEBD::initModel()
{
	_tModel = new EBDInfoModel(2, this);
	_tModel->setTableOption(EBDInfoModel::TableOption::HeaderTable);
	ui.tView->setModel(_tModel);
	ui.tView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MyDesignEditorEBD::initWindow()
{
	ui.tVDir->initView();
	QSettings settings("Sunstar", "BinaryFile");
	QString strLastPath = settings.value("LastOpenPath").toString();

	ui.lEPath->setText(strLastPath.replace("/", "\\"));

	ui.cBSort->addItem("Sort by name(Asc)");
	ui.cBSort->addItem("Sort by name(Des)");

	ui.lWImages->showDialogs(true);
	ui.lWImages->slotCurrentIndexChanged(0);
}

void MyDesignEditorEBD::initConnection()
{
	connect(ui.cBSort, SIGNAL(currentIndexChanged(int)), ui.lWImages, SLOT(slotCurrentIndexChanged(int)));

	connect(ui.tVDir, &FileDirTreeView::sigFiles, this, &MyDesignEditorEBD::slotSelectedFiles);
	connect(ui.lWImages, &DesignListWidget::sigClickedFile, this, &MyDesignEditorEBD::slotClickedFile);
	connect(ui.lWImages, &DesignListWidget::sigDoubleClickedFile, this, &MyDesignEditorEBD::slotDoubleClickedFile);

	connect(ui.lWImages, &DesignListWidget::sigSelectedRepeat, this, &MyDesignEditorEBD::slotSelectedRepeat);
	connect(ui.lWImages, &DesignListWidget::sigSelectedFiltering, this, &MyDesignEditorEBD::slotSelectedFiltering);
	connect(ui.lWImages, &DesignListWidget::sigSelectedStitEdit, this, &MyDesignEditorEBD::slotSelectedStitEdit);
	connect(ui.lWImages, &DesignListWidget::sigSelectedStitchDivide, this, &MyDesignEditorEBD::slotSelectedStitchDivide);
}

void MyDesignEditorEBD::initFormThema()
{
	qApp->setStyle(QStyleFactory::create("fusion"));

	QPalette palette;
	palette.setColor(QPalette::Window, QColor(53, 53, 53));
	palette.setColor(QPalette::WindowText, Qt::white);
	palette.setColor(QPalette::Base, QColor(15, 15, 15));
	palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
	palette.setColor(QPalette::ToolTipBase, Qt::white);
	palette.setColor(QPalette::ToolTipText, Qt::white);
	palette.setColor(QPalette::Text, Qt::white);
	palette.setColor(QPalette::Button, QColor(53, 53, 53));
	palette.setColor(QPalette::ButtonText, Qt::white);
	palette.setColor(QPalette::BrightText, Qt::red);

	palette.setColor(QPalette::Highlight, QColor(142, 45, 197).lighter());
	palette.setColor(QPalette::HighlightedText, Qt::black);
	qApp->setPalette(palette);
}

void MyDesignEditorEBD::initControlThread()
{
	_poolThread = NULL;
	_poolThread = new ControlThread(this);
	_poolThread->completeOneThread(true);
	connect(_poolThread, &ControlThread::sigFinished, this, &MyDesignEditorEBD::slotThFinished);
}

void MyDesignEditorEBD::slotLinEedit()
{
	ui.tVDir->setPath(ui.lEPath->text().replace("\\", "/"));
}

void MyDesignEditorEBD::slotSelectedFiles(const QString& path, const QStringList& files)
{
	if (_tModel != Q_NULLPTR)
	{
		_tModel->cleanModel();
		_tModel->reset();
	}

	_filesCount = files.count();
	_finishedThreadCount = 0;
	_finishedSuccessThreadCount = 0;

	ui.lEPath->setText(path);
	ui.lBFileCount->setText("");
	ui.lWImages->clear();

	if (files.count() == 0)
	{
		return;
	}

	Control::instance()->showLoading(this);

	_poolThread->setThreadCount(_poolThread->getMaxThreadCount());

	for each (QString strFile in files)
	{
		MakeDesignThread* thread = new MakeDesignThread(strFile);
		_poolThread->append(thread);
	}

	_poolThread->startWorking();
}

void MyDesignEditorEBD::slotThFinished(QThread* thread)
{
	_finishedThreadCount++;

	MakeDesignThread* th = qobject_cast<MakeDesignThread*>(thread);
	if (th->hasError())
	{
		qDebug() << "Could not read this '" << th->getFile() << "' file.";
	}
	else
	{
		_finishedSuccessThreadCount++;

		makeThumbNail(th);
		ui.lWImages->slotSetEbdiInfo(th->getEbdInfo());
	}

	ui.lBFileCount->setText(QString::number(_finishedSuccessThreadCount));

	if (_filesCount == _finishedThreadCount)
	{
		for each (MakeDesignThread* th in _poolThread->runThList())
		{
			delete th;
			th = Q_NULLPTR;
		}

		_poolThread->runThList().clear();
		Control::instance()->closeLoading();
	}
}

void MyDesignEditorEBD::makeThumbNail(MakeDesignThread* th)
{
	if (th->getSuffix() == Ebd)
	{
		QImage img = QImage::fromData(th->getEbdInfo().ebdHeader.ThumbNailData, "BMP");
		th->getEbdInfo().thumbNail = QPixmap::fromImage(img);
	}
	else
	{
		DrawDesign thumbNail;
		//QFuture<void> task = QtConcurrent::run(&thumbNail, &MakeSubThumbnail::makeThumbnail, &th->getEbdInfo());
		thumbNail.makeThumbnail(&th->getEbdInfo());
	}
}

void MyDesignEditorEBD::slotSelectedRepeat(const EbdFileInfo& ebdInfo)
{
	DialogRepeat dialog(ebdInfo);
	dialog.exec();
}

void MyDesignEditorEBD::slotSelectedFiltering(const EbdFileInfo& ebdInfo)
{
	DialogFiltering dialog(ebdInfo);
	dialog.exec();
}

void MyDesignEditorEBD::slotSelectedStitEdit(const EbdFileInfo& ebdInfo)
{
	DialogStitchEdit dialog(ebdInfo);
	dialog.exec();
}

void MyDesignEditorEBD::slotSelectedStitchDivide(const EbdFileInfo& ebdInfo)
{
	DialogStitchDivide dialog(ebdInfo);
	dialog.exec();
}

void MyDesignEditorEBD::slotClickedFile(const EbdFileInfo& ebdInfo)
{
	if (_tModel != Q_NULLPTR)
	{
		_tModel->setEbdInfo(ebdInfo);
		_tModel->reset();
	}
}

void MyDesignEditorEBD::slotDoubleClickedFile(const QString& strFile, const QIcon& icon)
{
	_selectedFile = strFile;
}