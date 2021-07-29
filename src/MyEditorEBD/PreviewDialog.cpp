#include "PreviewDialog.h"
#include "MakeDesign.h"

#include <QDebug>
#include <QFuture>
#include <QSettings>
#include <QListView>

#include <QtConcurrent/qtconcurrent>

PreviewDialog::PreviewDialog(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	initConnection();
	initControlThread();
	initDialog();

	setWindowModality(Qt::ApplicationModal);
}

PreviewDialog::~PreviewDialog()
{
	
}

void PreviewDialog::initDialog()
{
	ui.tVDir->initView();
	QSettings settings("Sunstar", "BinaryFile");
	QString strLastPath = settings.value("LastOpenPath").toString();

	ui.lEPath->setText(strLastPath.replace("/","\\"));

	ui.cBSort->addItem("Sort by name(Asc)");
	ui.cBSort->addItem("Sort by name(Des)");

	ui.lWImages->slotCurrentIndexChanged(0);
}

void PreviewDialog::initConnection()
{
	connect(ui.cBSort, SIGNAL(currentIndexChanged(int)), ui.lWImages, SLOT(slotCurrentIndexChanged(int)));

	connect(ui.lEPath, &QLineEdit::returnPressed, this, &PreviewDialog::slotLinEedit);
	connect(ui.tVDir, &FileDirTreeView::sigFiles, this, &PreviewDialog::slotSelectedFiles);
	connect(ui.lWImages, &DesignListWidget::sigSelectedFile, this, &PreviewDialog::slotSelectedFile);
}

void PreviewDialog::initControlThread()
{
	_poolThread = NULL;
	_poolThread = new ControlThread(this);
	_poolThread->completeOneThread(true);
	connect(_poolThread, &ControlThread::sigFinished, this, &PreviewDialog::slotThFinished);
}

void PreviewDialog::slotLinEedit()
{
	ui.tVDir->setPath(ui.lEPath->text().replace("\\", "/"));
}

void PreviewDialog::slotSelectedFiles(const QString& path, const QStringList& files)
{
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

void PreviewDialog::slotThFinished(QThread* thread)
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

void PreviewDialog::makeThumbNail(MakeDesignThread* th)
{
	if (th->getSuffix() == Ebd)
	{
		QImage img = QImage::fromData(th->getEbdInfo().ebdHeader.ThumbNailData, "BMP");
		th->getEbdInfo().thumbNail = QPixmap::fromImage(img);
	}
	else
	{  
		MakeDesign thumbNail;
		//QFuture<void> task = QtConcurrent::run(&thumbNail, &MakeDesign::makeThumbnail, &th->getEbdInfo());
		thumbNail.makeThumbnail(&th->getEbdInfo());
	}
}

void PreviewDialog::slotSelectedFile(const QString& strFile, const QIcon& icon)
{
	_selectedFile = strFile;
	_selectedIcon = icon;
	close();
}