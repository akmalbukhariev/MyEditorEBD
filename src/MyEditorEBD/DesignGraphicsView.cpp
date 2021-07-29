#include "DesignGraphicsView.h"

#include <QMouseEvent>

DesignGraphicsView::DesignGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	setMouseTracking(true);

	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

DesignGraphicsView::~DesignGraphicsView()
{
}

void DesignGraphicsView::resizeView()
{
	resetTransform();
	QRectF sceneR = sceneRect();
	if (this->width() < sceneR.width() || this->height() < sceneR.height())
	{
		float fWidth = this->width() / sceneR.width();
		float fHeight = (this->height()) / sceneR.height();
		float fMin;

		fMin = (fWidth > fHeight) ? fHeight : fWidth;

		scale(fMin, fMin);
	}
}

void DesignGraphicsView::wheelEvent(QWheelEvent* event)
{
	if (event->delta() > 0)
	{
		scale(1.1, 1.1);
	}
	else
	{
		scale(1 / 1.1, 1 / 1.1);
	}
}

void DesignGraphicsView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		//setCursor(Qt::OpenHandCursor);
	}
	else
	{
		QPointF img_coor_pt = mapToScene(event->pos());
		
		//setCursor(Qt::CrossCursor);
	}

	QGraphicsView::mousePressEvent(event);
}

void DesignGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
	QGraphicsView::mouseMoveEvent(event);
}

void DesignGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		//do something
	}
	QGraphicsView::mouseReleaseEvent(event);
}
