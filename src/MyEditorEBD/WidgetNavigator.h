#pragma once

#include <QWidget>

#include "ui_WidgetNavigator.h"
#include "ImageMapRectangleItem.h"

class WidgetNavigator : public QWidget
{
	Q_OBJECT

public:
	WidgetNavigator(QWidget *parent = Q_NULLPTR);
	~WidgetNavigator();

public slots:

	//Set a Pixmap.
	void setDesignMap(const QPixmap& pixmap);

private:
	void initConnections();
	void initGraphics();

private:

private:
	Ui::WidgetNavigator ui;

	QPixmap _pixmap;
	ImageMapRectangleItem* _rItem;
	QGraphicsPixmapItem* _imItem;
	QGraphicsScene* _scene;
};
