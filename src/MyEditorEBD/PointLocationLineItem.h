#pragma once

#include <QGraphicsItem>

#include "SewingGrid.h"

class PointLocationLineItem : public QGraphicsItem
{
public:
	PointLocationLineItem(QRect* viewRect, SewingGrid* xAxis, SewingGrid* yAxis, QGraphicsItem* parent = Q_NULLPTR);
	~PointLocationLineItem();

	void setPointInfo(const LinePoint& point);

	QRectF boundingRect() const override;

protected:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget *widget = nullptr) override;

private:
	LinePoint _pointInfo;

	QRect* _viewRect;

	SewingGrid* _xAxisGrid;
	SewingGrid* _yAxisGrid;
};
