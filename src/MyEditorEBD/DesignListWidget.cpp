#include "DesignListWidget.h"
#include "DesignPropertiesDialog.h"

#include <QToolTip>
#include <QFileInfo>
#include <QMouseEvent>

DesignListWidget::DesignListWidget(QWidget *parent)
	: QListWidget(parent)
{
	initView();
	initConnection();
}

DesignListWidget::~DesignListWidget()
{
}

void DesignListWidget::initView()
{
	setViewMode(IconMode);
	setIconSize(QSize(100, 100));
	setResizeMode(Adjust);
	sortItems(Qt::SortOrder::AscendingOrder);

	_actionIconMode = new QAction(this);
	_actionListMode = new QAction(this);
	_actionViewMode = new QAction(this);
	_actionProperties = new QAction(this);

	_actionIconMode->setCheckable(true);
	_actionListMode->setCheckable(true);
	_actionIconMode->setChecked(true);
	_actionListMode->setChecked(false);

	_actionIconMode->setText("Icon mode");
	_actionListMode->setText("List mode");
	_actionViewMode->setText("View mode");
	_actionProperties->setText("Properties");
	
	_menuMode.addAction(_actionIconMode);
	_menuMode.addAction(_actionListMode);

	_actionViewMode->setMenu(&_menuMode);

	_menu.addAction(_actionViewMode);
	_menu.addAction(_actionProperties);
}

void DesignListWidget::initConnection()
{
	connect(this, &QListWidget::itemDoubleClicked, this, &DesignListWidget::slotDoubleClickItem);
	connect(_actionIconMode, &QAction::triggered, this, &DesignListWidget::slotClickMenuAction);
	connect(_actionListMode, &QAction::triggered, this, &DesignListWidget::slotClickMenuAction);
	connect(_actionProperties, &QAction::triggered, this, &DesignListWidget::slotClickMenuAction);
}

void DesignListWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		clearSelection();
	}

	QListWidget::mousePressEvent(event);
}

void DesignListWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		QList< QListWidgetItem*> itemList = selectedItems();
		if (itemList.count() > 0)
		{
			EbdFileInfo ebdInfo = itemList[0]->data(Qt::UserRole).value< EbdFileInfo>();
			_menu.popup(mapToGlobal(event->pos()));
			_menu.show();
			/*QToolTip::showText(event->screenPos().toPoint(), makeText(ebdInfo));*/
		}
	}
	 
	QListWidget::mouseReleaseEvent(event);
}

void DesignListWidget::slotCurrentIndexChanged(int index)
{
	switch (index)
	{
		//case 0: break;
		case 0: sortItems(Qt::SortOrder::AscendingOrder); break;
		case 1: sortItems(Qt::SortOrder::DescendingOrder); break;
		default: break;
	}
}

void DesignListWidget::slotDoubleClickItem(QListWidgetItem* item)
{
	EbdFileInfo ebdInfo = item->data(Qt::UserRole).value< EbdFileInfo>();

	emit sigSelectedFile(ebdInfo.strFile, item->icon());
}

void DesignListWidget::slotSetEbdiInfo(const EbdFileInfo& ebdInfo)
{
	QVariant var;
	var.setValue(ebdInfo);

	QIcon icon = QIcon(ebdInfo.thumbNail);
	 
	if (icon.isNull() ) return;

	QFileInfo fInfo(ebdInfo.strFile);
	QListWidgetItem* newItem = new QListWidgetItem(icon, fInfo.baseName() + "." + fInfo.suffix());
	newItem->setData(Qt::UserRole, var);

	addItem(newItem);
}

void DesignListWidget::slotClickMenuAction()
{
	if (_actionIconMode == sender())
	{
		_actionIconMode->setChecked(true);
		_actionListMode->setChecked(false);
		setViewMode(IconMode);
	}
	else if (_actionListMode == sender())
	{
		_actionIconMode->setChecked(false);
		_actionListMode->setChecked(true);
		setViewMode(ListMode);
	}
	else if (_actionProperties == sender())
	{
		QList< QListWidgetItem*> itemList = selectedItems();
		if (itemList.count() > 0)
		{
			EbdFileInfo ebdInfo = itemList[0]->data(Qt::UserRole).value< EbdFileInfo>();
			DesignPropertiesDialog dialog(&ebdInfo);
			dialog.exec();
		}
	}
}

QString DesignListWidget::makeText(EbdFileInfo& ebdInfo)
{
	QString strText = "";
	strText.append("Design:        " + QString((char*)ebdInfo.ebdHeader.DesignName).trimmed() + "\n");
	strText.append("File Name:     " + QString((char*)ebdInfo.ebdHeader.FileName).trimmed() + "\n");
	strText.append("Size:          0\n");
	strText.append("Total Stitch:  " + QString::number(ebdInfo.ebdHeader.StitchCount) + "\n");
	strText.append("Color:         " + QString::number(ebdInfo.ebdHeader.ColorChangeNum) + "\n");
	strText.append("Jump:          " + QString::number(ebdInfo.ebdHeader.JumpNum));

	return strText;
}