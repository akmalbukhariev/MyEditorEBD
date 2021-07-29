#pragma once
 
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>

#include "SewingGrid.h"

class EditStitchesEllipseItem : public QGraphicsEllipseItem
{
public:
	EditStitchesEllipseItem(SewingGrid* xAxis, SewingGrid* yAxis, QGraphicsItem* parent = NULL);
	~EditStitchesEllipseItem();

	void setPointInfo(const LinePoint& point)
	{
		_linePoint = point;
	}

	QRectF boundingRect() const override; 

protected:
 
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

private:

	LinePoint _linePoint;

	SewingGrid* _xAxisGrid;
	SewingGrid* _yAxisGrid;
};
