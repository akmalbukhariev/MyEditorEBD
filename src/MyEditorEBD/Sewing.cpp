#include "Sewing.h"

#include <QDebug> 
#include <QThread>

Sewing::Sewing(SewingGrid* xAxis, SewingGrid* yAxis)
	:_xAxis(xAxis), _yAxis(yAxis)
{
	_partition = Q_NULLPTR;

	_btnMenu = BTN_NONE;
	_dotPen.setColor(Qt::black);
	//_dotPen.setWidth(10);
	_dotPen.setStyle(Qt::DotLine);
	_linePen.setColor(Qt::red);
}

Sewing::~Sewing()
{

}

void Sewing::setData(DataDesign* data)
{
	if (_partition == Q_NULLPTR)
	{
		_partition = new DesignPartition(data, this);
		_partition->setAxis(_xAxis, _yAxis);
		_partition->setStitchColor(_stitchColor);
	}
}

void Sewing::drawDesign(QPainter* painter)
{
	painter->setClipRect(_xAxis->getViewPort());

	if (_xAxis->getViewPort().width() == 0 && _yAxis->getViewPort().height() == 0) return;

	if (_partition == Q_NULLPTR) return;
	
	_partition->calcPartition();

	QPen dotPen;
	dotPen.setStyle(Qt::DotLine);

	LinePoint tempPoint = LinePoint();

	for (int i = 0; i < _partition->dataChanged()->count(); i++)
	{
		DesignPart& dPart = (*_partition->dataChanged())[i];

		for (int j = 0; j < dPart.points.count(); j++)
		{   
			const LinePoint& lPoint = dPart.points[j];
			switch (lPoint.type)
			{
				case NORMAL_CODE:
					painter->setPen(dPart.lineColor.color());
					break;
				case JUMP_CODE:
					dotPen.setColor(dPart.lineColor.color());
					painter->setPen(dotPen);
					break;
			}

			painter->drawLine(lPoint.startP, lPoint.endP);
			tempPoint = lPoint;
		}

		if (i + 1 < _partition->dataChanged()->count())
		{
			const DesignPart& tD = (*_partition->dataChanged())[i + 1];
			if (tD.points.count() != 0)
			{
				painter->drawLine(tempPoint.endP, tD.points[0].startP);
			}
		}

		if (dPart.isActive)
		{
			painter->setPen(QPen(Qt::blue, 2));
			painter->drawRect(dPart.border);
		}
	}

#pragma region MyRegion
	//float x1 = 0;
	//float y1 = 0;
	//int colorIndex = 1;

	//_linePen.setColor(_stitchColor[1]);
	//_dotPen.setColor(_stitchColor[1]);

	//CalcPoint calcPoint;
	//QList<QPoint> pList;

	//for (int i = 0; i < _pointList.count(); i++)
	//{
	//	if (i == _stCount) break;

	//	PointData& pData = _pointList[i];
	//	float x2 = pData.point.x() / 10;
	//	float y2 = pData.point.y() / 10;

	//	QPointF nextPoint = calcPoint.calcNextPoint(x1, y1, x2, y2);

	//	float wX1 = _xAxis->coordToPixel(x1);
	//	float wY1 = _yAxis->coordToPixel(y1);

	//	float wX2 = _xAxis->coordToPixel(nextPoint.x());
	//	float wY2 = _yAxis->coordToPixel(nextPoint.y());

	//	pList.append(QPoint(wX1, wY1));
	//	pList.append(QPoint(wX2, wY2));

	//	switch (pData.func)
	//	{
	//	case NORMAL_CODE:
	//		painter->setPen(_linePen);
	//		break;
	//	case CC_CODE:
	//		_linePen.setColor(_stitchColor[colorIndex]);
	//		_dotPen.setColor(_stitchColor[colorIndex]);
	//		colorIndex++;
	//		break;
	//	case JUMP_CODE:
	//		painter->setPen(_dotPen);

	//		DesignPart& dPart = DesignPart(i, pList);
	//		dPart.calcBorder();
	//		if (dPart.width() > 0 && dPart.height() > 0)
	//		{
	//			_dPartList.append(dPart);

	//			/*painter->setPen(QPen(Qt::blue, 2));
	//			painter->drawRect(dPart.border);*/
	//		}
	//		pList.clear();
	//		break;
	//	}

	//	painter->drawLine(QPointF(wX1, wY1), QPointF(wX2, wY2));
	//	x1 = nextPoint.x();
	//	y1 = nextPoint.y();
	//}
#pragma endregion
}

void Sewing::drawDesignPartBorder(QPoint& point, QPainter* painter)
{
	_designPart = _partition->getSelectedArea(point);

	if (_designPart.id > 0)
	{
		_designPart.isActive = false;
		painter->setPen(QPen(Qt::blue, 2));
		painter->drawRect(_designPart.border);
	}
}

void Sewing::unActivateSelectDesign(const QPoint& point)
{
	_designPart = _partition->getSelectedArea(point);
}

void Sewing::moveDesignPart(const QPoint& movePoint, const QPoint& clickPoint)
{
	if (_designPart.points.count() == 0) return;

	_partition->updateDesignPart(movePoint, clickPoint, _designPart);
}

void Sewing::unActiveAllDesignParts()
{
	for (int i = 0; i < _partition->data()->count(); i++)
	{
		DesignPart& dPart = (*_partition->data())[i];
		dPart.isActive = false;
	}
}

void Sewing::setStitchColor(const QColor& stColor, int needle)
{
	_stitchColor[needle] = stColor;
}

void Sewing::setStitchColor(const QList<QColor>& cList)
{
	_stitchColor = cList;
}

void Sewing::cleanColorTable()
{
	for (int i = 0; i < 16; i++)
	{
		_stitchColor[i] = QColor(Qt::black);
	}
}