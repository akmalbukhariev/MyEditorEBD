#include "Control.h"

#include<QScreen>
#include <QFileInfo>
#include <QMessageBox>

Control* Control::_self = Q_NULLPTR;

Control* Control::instance()
{
	if (_self == Q_NULLPTR)
		_self = new Control();

	return _self;
}

Control::Control(QObject *parent)
	: QObject(parent)
{
	_wLoading = new WidgetLoading();
}

Control::~Control()
{
}

void Control::addPixmapToNavigationList(int id, const QPixmap& pixmap)
{
	if (_navigationMapList.contains(NavigationMap(id)) == false)
	{
		_navigationMapList.append(NavigationMap(id, pixmap));
	}
}

void Control::updatePixmapInNavigationList(int id, const QPixmap& pixmap)
{
	for (int i = 0; i < _navigationMapList.count(); i++)
	{
		if (_navigationMapList[i]._id == id)
		{
			_navigationMapList[i]._pixmap = pixmap;
			emit sigUpdateNavigate(pixmap);
		}
	}
}
 
QPixmap Control::getPixmapFromNavigationList(int id)
{
	for(int i = 0; i < _navigationMapList.count(); i++)
	{
		if (_navigationMapList[i]._id == id)
		{
			return _navigationMapList[i]._pixmap;
		}
	}

	return QPixmap();
}

void Control::removePixmapFromNavigationList(int id)
{
	for (int i = 0; i < _navigationMapList.count(); i++)
	{
		if (_navigationMapList[i]._id == id)
		{
			_navigationMapList.removeAt(i);
		}
	}
}

void Control::designDataChanged()
{
	emit sigDesignDataChanged();
}

void Control::setClickPointInfoTable(const LinePoint& point)
{
	emit sigClickPointInfoTable(point);
}

void Control::setClickDesign(const LinePoint& point)
{
	emit sigClickDesign(point);
}

void Control::showLoading(QWidget* parent)
{
	//if (parent != Q_NULLPTR)
	//{
	//	// Get current screen size
	//	QRect rec = QGuiApplication::screenAt(parent->pos())->geometry();

	//	// Using minimum size of window
	//	QSize size = parent->minimumSize();

	//	// Set top left point
	//	QPoint topLeft = QPoint((rec.width() / 2) - (size.width() / 2), (rec.height() / 2) - (size.height() / 2));

	//	// set window position
	//	_wLoading->setGeometry(QRect(topLeft, size));
	//}
	
	//_wLoading->move( parent->parentWidget()->geometry().center() - parent->rect().center());

	//_wLoading->setParent(parent);
	_thLoading = new ThreadLoading(_wLoading, this);
	_thLoading->start();
}

void Control::showMessageBox(QWidget* parent, const QString& title, const QString& text, MsgOption option)
{
	switch (option)
	{
		case Control::Info:
			QMessageBox::information(parent, title, text, QMessageBox::Ok);
			break;
		case Control::Warring:
			QMessageBox::warning(parent, title, text, QMessageBox::Ok);
			break;
		case Control::Critical:
			QMessageBox::critical(parent, title, text, QMessageBox::Ok);
			break;
		default:
			break;
	}
}

void Control::setSelectedDesign(const QString& strFile)
{
	emit sigSelectedDesign(strFile);
}

void Control::setFileHasDropped(const QString& strFile)
{
	emit sigFileHasDropped(strFile);
}
 
FileSuffix Control::fileSuffix(const QString& strFile)
{
	FileSuffix suffix = FileSuffix::NoneFile;

	QFileInfo fInfo(strFile);
	if (fInfo.suffix().toUpper() == "SST")
	{
		suffix = FileSuffix::Sst;
	}
	else if (fInfo.suffix().toUpper() == "EBD")
	{
		suffix = FileSuffix::Ebd;
	}
	else if (fInfo.suffix().toUpper() == "DST")
	{
		suffix = FileSuffix::Dst;
	}
	else if (fInfo.suffix().toUpper() == "TBF")
	{
		suffix = FileSuffix::Tbf;
	}

	return suffix;
}

void Control::cleanAllModels(const QString& strFile)
{
	emit sigCleanAllModels(strFile);
}

void Control::closeLoading()
{
	if (_thLoading != Q_NULLPTR)
	{
		_wLoading->close();
		delete _thLoading;
		_thLoading = Q_NULLPTR;
	}
}