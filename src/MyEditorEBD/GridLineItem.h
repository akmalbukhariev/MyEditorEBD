#pragma once

#include <QGraphicsItem>

#include "SewingGrid.h"

class GridLineItem : public QGraphicsItem
{
public:
	GridLineItem(SewingGrid* xAxis, SewingGrid* yAxis, QGraphicsItem* parent = 0);
	~GridLineItem();

	QRectF boundingRect() const override;

protected:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:

	SewingGrid* _xAxis;
	SewingGrid* _yAxis;
};
