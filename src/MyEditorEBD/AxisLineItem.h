#pragma once

#include <QPen>
#include <QGraphicsItem>

#include "CommonDef.h"

class AxisLineItem : public QGraphicsItem
{
public:
	AxisLineItem(QRect* viewRect, int wWidth, int hHeight, QGraphicsItem* parent = Q_NULLPTR);
	~AxisLineItem();

	void updateSize(int width, int height)
	{
		_width = width;
		_height = height;
	}

	void setAxisColor(const QColor& color)
	{
		_axisPen = color;
	}

	QRectF boundingRect() const override;

protected:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget *widget = nullptr) override;

private:
	int _width;
	int _height;

	QPen _axisPen;
	QRect* _viewRect;
};
