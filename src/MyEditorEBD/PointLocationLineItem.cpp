#include "PointLocationLineItem.h"

PointLocationLineItem::PointLocationLineItem(QRect* viewRect, SewingGrid* xAxis, SewingGrid* yAxis, QGraphicsItem* parent)
	:_viewRect(viewRect), QGraphicsItem(parent)
{
	_xAxisGrid = xAxis;
	_yAxisGrid = yAxis;
}

PointLocationLineItem::~PointLocationLineItem()
{

}

void PointLocationLineItem::setPointInfo(const LinePoint& point)
{
	_pointInfo = point;
}

void PointLocationLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget *widget)
{
	if (_viewRect == NULL || !_pointInfo.isValid()) return;
	if (_xAxisGrid == NULL || _yAxisGrid == NULL) return;

	float x = _xAxisGrid->coordToPixel(_pointInfo.startP.x());
	float y = _yAxisGrid->coordToPixel(_pointInfo.startP.y());
	x = qRound(x);
	y = qRound(y);

	painter->setPen(QPen(Qt::red, 1));
	painter->drawLine(x, _viewRect->y(), x, _viewRect->bottom());
	painter->drawLine(_viewRect->x(), y, _viewRect->right(), y);
}

QRectF PointLocationLineItem::boundingRect() const
{
	return QRectF();
}