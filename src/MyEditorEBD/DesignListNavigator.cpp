#include "CCTableDialog.h"
#include "DesignListNavigator.h"

#include <QMouseEvent>

DesignListNavigator::DesignListNavigator(QWidget* parent)
	: QListWidget(parent)
{
	initView();
	initMenu();
	initConnection();
}

DesignListNavigator::~DesignListNavigator()
{

}

void DesignListNavigator::initView()
{
	setViewMode(IconMode);
	setIconSize(QSize(100, 100));
	setResizeMode(Adjust);

	setViewMode(ListMode);
}

void DesignListNavigator::initMenu()
{
	_actionCCTable = new QAction(this);
	_actionCCTable->setText("Manege C/C Table");;
	_menu.addAction(_actionCCTable);
}

void DesignListNavigator::initConnection()
{
	connect(this, &QListWidget::itemClicked, this, &DesignListNavigator::slotOnListMailItemClicked);
	connect(Control::instance(), &Control::sigCleanAllModels, this, &DesignListNavigator::removeDesign);
	//connect(this, &QListWidget::itemDoubleClicked, this, &DesignListNavigator::slotDoubleClickItem);

	connect(_actionCCTable, &QAction::triggered, this, &DesignListNavigator::slotClickMenuAction);
}

void DesignListNavigator::mousePressEvent(QMouseEvent* event)
{
	_click = false;
	if (event->button() == Qt::LeftButton)
	{
		_click = true;
	}

	QListWidget::mousePressEvent(event);
}

void DesignListNavigator::mouseReleaseEvent(QMouseEvent* event)
{
	/*if (event->button() == Qt::RightButton)
	{
		QList< QListWidgetItem*> itemList = selectedItems();
		if (itemList.count() > 0)
		{
			_menu.popup(mapToGlobal(event->pos()));
			_menu.show();
		}
	}*/

	QListWidget::mouseReleaseEvent(event);
}

void DesignListNavigator::slotClickMenuAction()
{
	/*CCTableDialog d(_ebdInfo);
	d.exec();*/
}

void DesignListNavigator::slotOnListMailItemClicked(QListWidgetItem* item)
{
	if (!_click) return;

	QString strFile = item->data(Qt::UserRole).value<QString>();
	Control::instance()->setSelectedDesign(strFile);
}

void DesignListNavigator::slotDoubleClickItem(QListWidgetItem* item)
{

}

void DesignListNavigator::addDesign(const QIcon& icon, const QString& iconFileName)
{
	if (!exist(iconFileName))
	{
		QVariant var;
		var.setValue(iconFileName);
		QListWidgetItem* newItem = new QListWidgetItem(icon, "");
		newItem->setData(Qt::UserRole, var);

		addItem(newItem);
		clearSelection();
		setItemSelected(newItem, true);
	}
}

void DesignListNavigator::removeDesign(const QString& iconFileName)
{
	for (int i = 0; i < count(); i++)
	{
		QListWidgetItem* wItem = item(i);
		QString strFile = wItem->data(Qt::UserRole).value<QString>();

		if (iconFileName == strFile)
		{
			takeItem(i); 
		}
	}
}

void DesignListNavigator::addDesign(WidgetWokrDesign* design)
{
	if (design == nullptr) return;

	design->update();
	if (!exist(design))
	{
		QVariant var;
		var.setValue(design->getFileName());
		QPixmap p = design->getDesignMap();
		p = p.scaled(200, 200);
		QIcon icon = QIcon(p);

		QListWidgetItem* newItem = new QListWidgetItem(icon, "");
		newItem->setData(Qt::UserRole, var);

		addItem(newItem);
	}
}

void DesignListNavigator::selectItemFile(const QString& iconFileName)
{
	for (int i = 0; i < count(); i++)
	{
		QListWidgetItem* wItem = item(i);
		QString strFile = wItem->data(Qt::UserRole).value<QString>();

		if (iconFileName == strFile)
		{
			clearSelection();
			setItemSelected(wItem, true);
		}
	}
}

bool DesignListNavigator::exist(WidgetWokrDesign* design)
{
	bool found = false;
	for (int i = 0; i < count(); i++)
	{
		QListWidgetItem* wItem = item(i);

		QString strFile = wItem->data(Qt::UserRole).value<QString>();

		if (design->getFileName() == strFile)
		{
			QPixmap p = design->getDesignMap();
			p = p.scaled(200, 200);
			QIcon icon = QIcon(p);

			wItem->setIcon(icon);
			found = true;
		}
	}

	return found;
}

bool DesignListNavigator::exist(const QString& iconFileName)
{
	for (int i = 0; i < count(); i++)
	{
		QListWidgetItem* wItem = item(i);

		if (wItem == nullptr) continue;

		QString strFile = wItem->data(Qt::UserRole).value<QString>();

		if (iconFileName == strFile)
		{
			return true;
		}
	}

	return false;
}