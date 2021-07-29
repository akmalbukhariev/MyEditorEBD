#include "ImageMapRectangleItem.h"

ImageMapRectangleItem::ImageMapRectangleItem(QGraphicsRectItem* parent)
	:QGraphicsRectItem(parent),m_dragged(false)
{
	setFlags(QGraphicsItem::ItemIsSelectable |
		QGraphicsItem::ItemIsMovable);
}

ImageMapRectangleItem::~ImageMapRectangleItem()
{
}

void ImageMapRectangleItem::setAnchorPoint(const QPointF &anchorPoint) 
{
	this->anchorPoint = anchorPoint;
}

void ImageMapRectangleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) 
{
	m_dragged = true;
	QGraphicsRectItem::mouseMoveEvent(event);
}

void ImageMapRectangleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) 
{
	if (m_dragged) 
	{
		QList<QGraphicsItem*> colItems = collidingItems();
		if (colItems.isEmpty())
			this->setPos(anchorPoint);
		else 
		{
			QGraphicsItem* closestItem = colItems.at(0);
			qreal shortestDist = 100000;
			foreach(QGraphicsItem* item, colItems) 
			{
				QLineF line(item->sceneBoundingRect().center(),
					this->sceneBoundingRect().center());
				if (line.length() < shortestDist) 
				{
					shortestDist = line.length();
					closestItem = item;
				}
			}
			this->setPos(closestItem->scenePos());
		}
		m_dragged = false;
	}
	QGraphicsRectItem::mouseReleaseEvent(event);
}