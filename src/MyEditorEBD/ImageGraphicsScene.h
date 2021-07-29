#pragma once

#include <QGraphicsScene>

class ImageGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	ImageGraphicsScene(QObject *parent);
	~ImageGraphicsScene();
};
