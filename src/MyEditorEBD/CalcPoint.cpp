#include "CalcPoint.h"

#include <qmath.h>

CalcPoint::CalcPoint()
{
}

CalcPoint::~CalcPoint()
{
}

QPointF CalcPoint::calcNextPoint(float x1, float y1, float x2, float y2)
{
	float diffX = x2 - x1;
	float diffY = y2 - y1;
	_length = qSqrt(diffX * diffX + diffY * diffY);

	bool isX1_Negative = false;
	bool isX2_Negative = false;
	bool isY1_Negative = false;
	bool isY2_Negative = false;

	if (x1 < 0) isX1_Negative = true;
	if (x2 < 0) isX2_Negative = true;
	if (y1 < 0) isY1_Negative = true;
	if (y2 < 0) isY2_Negative = true;

	float newX = 0;
	float newY = 0;

	x1 = qAbs(x1);
	x2 = qAbs(x2);

	if (isX1_Negative && isX2_Negative)
	{
		newX = -1 * (x1 + x2);
	}
	else if (isX1_Negative && !isX2_Negative)
	{
		newX = (x1 > x2) ? -1 * (x1 - x2) : x2 - x1;
	}
	else if (!isX1_Negative && isX2_Negative)
	{
		newX = (x1 < x2) ? -1 * (x2 - x1) : x1 - x2;
	}
	else if (!isX1_Negative && !isX2_Negative)
	{
		newX = x1 + x2;
	}

	y1 = qAbs(y1);
	y2 = qAbs(y2);

	if (isY1_Negative && isY2_Negative)
	{
		newY = -1 * (y1 + y2);
	}
	else if (isY1_Negative && !isY2_Negative)
	{
		newY = (y1 > y2) ? -1 * (y1 - y2) : y2 - y1;
	}
	else if (!isY1_Negative && isY2_Negative)
	{
		newY = (y1 < y2) ? -1 * (y2 - y1) : y1 - y2;
	}
	else if (!isY1_Negative && !isY2_Negative)
	{
		newY = y1 + y2;
	}

	return QPointF(newX, newY);
}
