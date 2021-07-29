#pragma once

#include <QGraphicsPixmapItem>

class ImageItem : public QGraphicsPixmapItem
{ 

public:
	ImageItem(QGraphicsPixmapItem* parent = 0);
	~ImageItem();
};
