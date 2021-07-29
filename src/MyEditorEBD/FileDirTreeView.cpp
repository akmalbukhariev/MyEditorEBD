#include "FileDirTreeView.h"

#include <QDir>
#include <QSettings>

FileDirTreeView::FileDirTreeView(QWidget* parent)
	: QTreeView(parent)
{
	initConnection();
}

FileDirTreeView::~FileDirTreeView()
{

}

void FileDirTreeView::initView()
{
	QSettings settings("Sunstar", "BinaryFile");
	QString strLastPath = settings.value("LastOpenPath").toString();

	_dirModel = new QDirModel(this);
	_dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
	setModel(_dirModel);

	for (int i = 1; i < _dirModel->columnCount(); i++)
	{
		hideColumn(i);
	}

	openDir(strLastPath);
}

void FileDirTreeView::initConnection()
{
	connect(this, &QTreeView::clicked, this, &FileDirTreeView::slotClickTreeView);
}

void FileDirTreeView::setPath(const QString& path)
{
	openDir(path);
}

void FileDirTreeView::openDir(const QString& path)
{
	// Set initial selection
	QModelIndex index = _dirModel->index(path);

	// Set initial view of directory 
	// for the selected drive as expanded
	expand(index);

	// Make it scroll to the selected
	scrollTo(index);

	// Highlight the selected
	setCurrentIndex(index);

	// Resizing the column - first column
	resizeColumnToContents(0);

	slotClickTreeView(index);
}

void FileDirTreeView::slotClickTreeView(const QModelIndex& index)
{
	if (!index.isValid()) return;

	QString strPath = _dirModel->filePath(index);

	QDir dir(strPath);
	QStringList files;
	for each (QFileInfo fInfo in dir.entryInfoList())
	{
		QString strSuffix = fInfo.suffix().toUpper();

		if (strSuffix == "SST" || strSuffix == "EBD" || strSuffix == "DST" || strSuffix == "TBF")
		{
			QString strFile = fInfo.absoluteFilePath();
			files.append(strFile);
		}
	}

	saveLastFolder(strPath);
	emit sigFiles(strPath.replace("/","\\"), files);
}

void FileDirTreeView::saveLastFolder(const QString& path)
{
	QSettings settings("Sunstar", "BinaryFile");
	QString strLastPath = settings.value("LastOpenPath").toString();
	
	settings.setValue("LastOpenPath", path);
}