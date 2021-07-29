#pragma once

#include <QPoint>

class CalcPoint
{
public:
	CalcPoint();
	~CalcPoint();

	QPointF calcNextPoint(float x1, float y1, float x2, float y2);

	float getLength() const
	{
		return _length;
	}

private:

	int _length;
};
