#pragma once

#include <QGraphicsRectItem>

class ImageMapRectangleItem : public QGraphicsRectItem
{
	 
public:
	ImageMapRectangleItem(QGraphicsRectItem* parent = 0);
	~ImageMapRectangleItem();

	void setAnchorPoint(const QPointF& anchorPoint);

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
	QPointF anchorPoint;
	bool m_dragged;
};
