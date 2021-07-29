#include "GridLineItem.h"

GridLineItem::GridLineItem(SewingGrid* xAxis, SewingGrid* yAxis, QGraphicsItem* parent)
	:_xAxis(xAxis), _yAxis(yAxis), QGraphicsItem(parent)
{
}

GridLineItem::~GridLineItem()
{
}

void GridLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (_xAxis == NULL || _yAxis == NULL) return;

	_xAxis->replot(painter);
	_yAxis->replot(painter);
}

QRectF GridLineItem::boundingRect() const
{
	return QRectF();
}