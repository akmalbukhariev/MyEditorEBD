#include "CalcPoint.h"
#include "DesignPartition.h"

#include <QDebug>

DesignPartition::DesignPartition(DataDesign* data, QObject *parent)
	: _data(data), QObject(parent)
{
	_dataChanged = Q_NULLPTR;
	_dataChanged = new DataDesign();

	_xRealAxis = new SewingGrid(SAxis::sXAxis);
	_yRealAxis = new SewingGrid(SAxis::sYAxis);

	_xRealAxis->setAxisRange(-127, 127);
	_yRealAxis->setAxisRange(-127, 127);
}

DesignPartition::~DesignPartition()
{
	if (_dataChanged != Q_NULLPTR)
	{
		delete _dataChanged;
		_dataChanged = Q_NULLPTR;
	}
}

void DesignPartition::setAxis(SewingGrid* xAxis, SewingGrid* yAxis)
{
	_xAxis = xAxis;
	_yAxis = yAxis; 
}

void DesignPartition::setStitchColor(const QList<QColor>& stitchColor)
{
	_stitchColor = stitchColor;
}

void DesignPartition::calcPartition()
{
	_dataChanged->clear();

	float xMin = 0;
	float xMax = 0;
	float yMin = 0;
	float yMax = 0;

	if (_data->count() != 0)
	{
		DesignPart dPart = (*_data)[0];
		if (dPart.points.count() != 0)
		{
			LinePoint& p = dPart.points[0];
			xMin = _xAxis->coordToPixel(p.startP.x());
			xMax = _xAxis->coordToPixel(p.startP.x());

			yMin = _yAxis->coordToPixel(p.startP.y());
			yMax = _yAxis->coordToPixel(p.startP.y());
		}
	}

	for (int i = 0; i < _data->count(); i++)
	{
		DesignPart dPart = (*_data)[i];

		for(int j = 0; j < dPart.points.count(); j++)
		{
			LinePoint& p = dPart.points[j];

			float wX1 = _xAxis->coordToPixel(p.startP.x());
			float wY1 = _yAxis->coordToPixel(p.startP.y());

			float wX2 = _xAxis->coordToPixel(p.endP.x());
			float wY2 = _yAxis->coordToPixel(p.endP.y());

			p.startP.setX(wX1);
			p.startP.setY(wY1);

			p.endP.setX(wX2);
			p.endP.setY(wY2);

			/*xMin = qMin(qMin(wX1, wX2), xMin);
			xMax = qMax(qMax(wX1, wX2), xMax);

			yMin = qMin(qMin(wY1, wY2), yMin);
			yMax = qMax(qMax(wY1, wY2), yMax);*/
		}

		dPart.calcBorder();
		_dataChanged->append(dPart);
	}

	_designRect = QRect(xMin, yMin, xMax - xMin, yMax - yMin);

	/*qDebug() << "xMin :" << xMin;
	qDebug() << "xMax :" << xMax;

	qDebug() << "yMin :" << yMin;
	qDebug() << "yMax :" << yMax;*/
}

void DesignPartition::updateDesignPart(const QPoint& movePoint, const QPoint& clickPoint, DesignPart& dPart)
{
	float clickX = _xAxis->pixelToCoord(clickPoint.x());
	float clickY = _yAxis->pixelToCoord(clickPoint.y());

	float moveX = _xAxis->pixelToCoord(movePoint.x());
	float moveY = _yAxis->pixelToCoord(movePoint.y());

	_xRealAxis->setViewPort(_xAxis->getViewPort());
	_yRealAxis->setViewPort(_yAxis->getViewPort());

	float clickRX = _xRealAxis->pixelToCoord(clickPoint.x());
	float clickRY = _yRealAxis->pixelToCoord(clickPoint.y());

	float moveRX = _xRealAxis->pixelToCoord(movePoint.x());
	float moveRY = _yRealAxis->pixelToCoord(movePoint.y());

	QPointF res = QPointF(clickX - moveX, clickY - moveY);
	QPointF resR = QPointF(clickRX - moveRX, clickRY - moveRY);

	for (int i = 0; i < _data->count(); i++)
	{
		DesignPart& d = (*_data)[i];
		if (d.id == dPart.id)
		{
			d.isActive = true;
			bool entered = false;

			for (int j = 0; j < d.points.count(); j++)
			{
				entered = true;
				
				LinePoint& lPoint = d.points[j];

				lPoint.startP.setX(lPoint.startP.x() - res.x());
				lPoint.startP.setY(lPoint.startP.y() - res.y());

				lPoint.endP.setX(lPoint.endP.x() - res.x());
				lPoint.endP.setY(lPoint.endP.y() - res.y());
				
				if (j == 0)
				{
					lPoint.realPoint.setX(lPoint.realPoint.x() - res.x());
					lPoint.realPoint.setY(lPoint.realPoint.y() - res.y());  

					/*if (lPoint.realPoint.x() >= 120 || lPoint.realPoint.x() <= -120)
					{
						lPoint.biggerRangeCount++;
					}
					else if (lPoint.realPoint.y() >= 120 || lPoint.realPoint.y() <= -120)
					{
						lPoint.biggerRangeCount++;
					}*/
				}

				#pragma region Another method
				/*QPointF res = QPointF(clickX - moveX, clickY - moveY);

				lPoint.startP.setX(lPoint.startP.x() - res.x());
				lPoint.startP.setY(lPoint.startP.y() - res.y());

				lPoint.endP.setX(lPoint.endP.x() - res.x());
				lPoint.endP.setY(lPoint.endP.y() - res.y());*/
				#pragma endregion
			}

			if (entered)
			{
				//dPart = d;
				return;
			}
		}
		else
		{
			d.isActive = false;
		}
	}
}

DesignPart DesignPartition::getSelectedArea(const QPoint& point)
{
	QList<DesignPart> recList;
	for (int i = 0; i < _dataChanged->count(); i++)
	{
		const DesignPart& var = _dataChanged->at(i);

		if (var.border.contains(point))
		{
			if (var.width() > 0 && var.height() > 0)
			{
				recList.append(var);
			}
		}
	}

	int maxId = 0;
	if (recList.count() > 0)
		maxId = recList[0].id;

	DesignPart d;
	for each (DesignPart v in recList)
	{
		if (maxId <= v.id)
		{
			d = v;
			maxId = v.id;
		}
	}

	return d;
}

void DesignPartition::removeDesignPart(const DesignPart& dPart)
{
	for (int i = 0; i < _data->count(); i++)
	{
		DesignPart& d = (*_data)[i];
		if (d.id == dPart.id)
		{
			d.removed = true;

			//do something
		}
	}
}