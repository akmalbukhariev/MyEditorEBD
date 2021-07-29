#include "AxisLineItem.h"

AxisLineItem::AxisLineItem(QRect* viewRect, int wWidth, int hHeight, QGraphicsItem* parent)
	:_viewRect(viewRect), QGraphicsItem(parent)
{
	_width = wWidth;
	_height = hHeight;
	_axisPen = QPen(Qt::white, 1);
}

AxisLineItem::~AxisLineItem()
{
}

void AxisLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget* widget)
{
	painter->setPen(_axisPen);

	int upLeftX = _viewRect->left();
	int upLeftY = CommonDef::Margin - 5;
	int lowLeftX = _viewRect->left();
	int lowLeftY = _viewRect->bottom();
	int lowRightX = _viewRect->right();

	QPointF upLeft(upLeftX, upLeftY);
	QPointF lowLeft(lowLeftX, lowLeftY);
	QPointF lowReight(lowRightX, lowLeftY);

	QPointF xUpAxis(_width - upLeftX - 5, _height - upLeftY - 10);
	QPointF xDownAxis(_width - upLeftX - 5, lowLeftY + 5);

	/*Coordinate*/
	painter->drawLine(lowLeft, lowReight);
	painter->drawLine(xUpAxis, lowReight);
	painter->drawLine(lowReight, xDownAxis);

	/*Axis*/
	QPointF yLeftAxis(upLeftX - 5, upLeftY + 5);
	QPointF yReightAxis(upLeftX + 5, upLeftY + 5);

	painter->drawLine(upLeft, lowLeft);
	painter->drawLine(yLeftAxis, upLeft);
	painter->drawLine(upLeft, yReightAxis);
}

QRectF AxisLineItem::boundingRect() const
{
	return QRectF();
}