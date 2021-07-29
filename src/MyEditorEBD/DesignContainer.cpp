#include "DesignContainer.h"

#include <QDebug>
#include <qmimedata.h>
#include <QMouseEvent>
#include <QMdiSubWindow>

DesignContainer::DesignContainer(QWidget *parent)
	:QMdiArea(parent)
{
	_navigateId = 0;

	setAcceptDrops(true);
	initConnections();
}

DesignContainer::~DesignContainer()
{
}

void DesignContainer::initConnections()
{
	connect(Control::instance(), &Control::sigClickPointInfoTable, this, &DesignContainer::slotClickPointInfoTable);
}

void DesignContainer::dragEnterEvent(QDragEnterEvent* event)
{
	event->accept();
}

void DesignContainer::dragMoveEvent(QDragMoveEvent* event)
{
	event->accept();
}

void DesignContainer::dropEvent(QDropEvent* event)
{
	QList<QUrl> urls = event->mimeData()->urls();

	if (urls.count() > 0)
	{
		//QString fileName = urls.first().toLocalFile();
		//addWindow(fileName);
	}
}

void DesignContainer::addWindow(const QString& fileName)
{
	_hasError = false;

	if (checkFile(fileName)) return;

	_fileName = fileName;

	WidgetWokrDesign* wDesign = new WidgetWokrDesign(fileName, this);
	//wDesign->setDesignIcon(fileIcon);
	wDesign->setStitchColor(_stitchColor);
	
	//connect(wDesign, &WidgetWokrDesign::sigFileHasDropped, this, &DesignContainer::addWindow);
	connect(wDesign, &WidgetWokrDesign::sigDesignDataChanged, this, &DesignContainer::slotDesignDataChanged);
	connect(wDesign, &WidgetWokrDesign::sigWorkDesignClosing, this, &DesignContainer::slotWorkDesignClosing);

	if (wDesign->drawDesign(_navigateId))
	{
		//Control::instance()->addPixmapToNavigationList(_navigateId);

		emit sigDesignDataChanged(wDesign);
		addSubWindow(wDesign);
		wDesign->showMaximized();

		_navigateId++;
		_hasError = false;
	}
	else
	{
		_hasError = true;

		delete wDesign;
		wDesign = Q_NULLPTR;
		//_fileName = "";
		Control::instance()->showMessageBox(this, "Read file", "Could not read.", Control::MsgOption::Warring);
	}
}

void DesignContainer::slotDesignDataChanged()
{
	emit sigDesignDataChanged(getActiveDesignWindow());
}

void DesignContainer::slotClickPointInfoTable(const LinePoint& point)
{
	WidgetWokrDesign* dWidget = getActiveDesignWindow();
	if (dWidget != Q_NULLPTR)
	{
		dWidget->setClickPointInfo(point);
	}
}

WidgetWokrDesign* DesignContainer::getActiveDesignWindow()
{
	QMdiSubWindow* sWindow = activeSubWindow();
	if (sWindow != Q_NULLPTR)
		return qobject_cast<WidgetWokrDesign*>(activeSubWindow()->widget());

	return Q_NULLPTR;
}

void DesignContainer::setActiveWindow(const QString& strFile)
{
	for (int i = 0; i < subWindowList().count(); i++)
	{
		QMdiSubWindow* sWindow = subWindowList()[i];
		WidgetWokrDesign* window = qobject_cast<WidgetWokrDesign*>(sWindow->widget());
		if (window != nullptr && window->getFileName() == strFile)
		{
			setActiveSubWindow(sWindow);
		}
	}
}

const QPixmap& DesignContainer::getDesignMap()
{
	WidgetWokrDesign* wD = getActiveDesignWindow();
	if (wD != NULL) return wD->getDesignMap();

	return QPixmap();
}

void DesignContainer::setStitchColor(const QList<QColor>& cList)
{
	 _stitchColor = cList; 
}

void DesignContainer::slotWorkDesignClosing(WidgetWokrDesign* wDesign)
{
	Control::instance()->cleanAllModels(wDesign->getFileName());

	delete wDesign;
	wDesign = Q_NULLPTR;
}

bool DesignContainer::checkFile(const QString& strFile)
{
	bool yes = false;
	for each (QMdiSubWindow* var in subWindowList())
	{
		WidgetWokrDesign* w = qobject_cast<WidgetWokrDesign*>(var->widget());

		if (w->getFileName() == strFile)
		{
			yes = true;
			break;
		}
	}

	return yes;
}