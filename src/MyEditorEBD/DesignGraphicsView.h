#pragma once

#include <QGraphicsView>

class DesignGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	DesignGraphicsView(QWidget *parent);
	~DesignGraphicsView();

	//Resize a Image
	void resizeView();

protected:
	void wheelEvent(QWheelEvent * event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
};
