#include "EditStitchesEllipseItem.h"

#include <QDebug>

EditStitchesEllipseItem::EditStitchesEllipseItem(SewingGrid* xAxis, SewingGrid* yAxis, QGraphicsItem* parent)
	:_xAxisGrid(xAxis), _yAxisGrid(yAxis), QGraphicsEllipseItem(parent)
{

}

EditStitchesEllipseItem::~EditStitchesEllipseItem()
{

}

void EditStitchesEllipseItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	if (!_linePoint.isValid()) return;

	int rX1 = _xAxisGrid->pixelToCoord(5);
	int rY1 = rX1;//_yAxisGrid->coordToPixel(20);

	qDebug() << rX1;

	QPoint point;

	painter->setBrush(QBrush(Qt::cyan));
	painter->drawEllipse(_linePoint.endP, rX1, rY1);
}

QRectF EditStitchesEllipseItem::boundingRect() const
{
	return QRectF();
}