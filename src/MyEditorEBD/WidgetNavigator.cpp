#include "WidgetNavigator.h"

#include "Control.h"

WidgetNavigator::WidgetNavigator(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	initGraphics();
	initConnections();

	QRectF rect(0, 0, 80, 40);
	QBrush myBrush(Qt::darkGray, Qt::Dense5Pattern);

	_rItem->setRect(rect);
	_rItem->setPos(30, 100);
	_rItem->setBrush(QBrush(QColor("#ffa07a")));
	_rItem->setAnchorPoint(_rItem->pos());

	//ui.designView->setBackgroundBrush(QBrush())
}

WidgetNavigator::~WidgetNavigator()
{

}

void WidgetNavigator::initConnections()
{
	connect(Control::instance(), &Control::sigUpdateNavigate, this, &WidgetNavigator::setDesignMap);
}

void WidgetNavigator::initGraphics()
{
	_rItem = new ImageMapRectangleItem;
	_imItem = new QGraphicsPixmapItem;
	_scene = new QGraphicsScene(this);

	//_scene->setSceneRect(ui.designView->rect());  
	//ui.designView->fitInView(_scene->itemsBoundingRect(), Qt::KeepAspectRatioByExpanding);
	ui.designView->setScene(_scene);
	//ui.designView->setBackgroundBrush(QBrush(QColor("#505050")));

	_scene->addItem(_imItem);
	//_scene->addItem(_rItem);
}

void WidgetNavigator::setDesignMap(const QPixmap& pixmap)
{
	_pixmap = pixmap;
	 
	_imItem->setPos(0, 0);
	_imItem->setPixmap(pixmap);
}