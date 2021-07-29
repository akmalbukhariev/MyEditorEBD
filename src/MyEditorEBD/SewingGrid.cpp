#include "SewingGrid.h"
#include "STickCalculation.h"

SewingGrid::SewingGrid(SAxis sAxis)
{
	_sAxis = sAxis;
}

SewingGrid::SewingGrid()
{

}

SewingGrid::~SewingGrid()
{
}

void SewingGrid::setAxisRange(double min, double max)
{
	_axisRange.lower = min;
	_axisRange.upper = max;
}

void SewingGrid::addAxisLabel(double position, QString label)
{
	_lList.insert(position, label);
}

void SewingGrid::setLinePen(const QPen& linePen, const QPen& labelPen)
{
	_lPen.linePen = linePen;
	_lPen.labelPen = labelPen;
}

void SewingGrid::replot(QPainter* painter)
{
	_ticks.clear();
	_ticks = STickCalculation::getTicks(_axisRange);

	QString strLabel = QString::null;

	for (int i = 0; i < _ticks.count(); i++)
	{
		double label = _ticks.at(i);
		double point = coordToPixel(label);

		switch (_sAxis)
		{
			case sXAxis:
			{
				drawVerticalLine(painter, point);
				drawLabelX(painter, point, QString::number(label));
			}
			break;
			case sYAxis:
			{
				drawHorizontalLine(painter, point);
				drawLabelY(painter, point, QString::number(label));
			}
			break;
		}
	}
}

void SewingGrid::scaleRange(double factor, double center)
{
	SAxisRange newRange;
	newRange.lower = (_axisRange.lower - center) * factor + center;
	newRange.upper = (_axisRange.upper - center) * factor + center;

	_axisRange = newRange;
}

void SewingGrid::moveGrid(const QPoint& startPoint, const QPoint& endPoint)
{
	double diff = 0.0;
	if (_sAxis == sXAxis)
	{
		diff = pixelToCoord(startPoint.x()) - pixelToCoord(endPoint.x());
	}
	else
	{
		diff = pixelToCoord(startPoint.y()) - pixelToCoord(endPoint.y());
	}

	_axisRange.lower = _axisRange.lower + diff;
	_axisRange.upper = _axisRange.upper + diff;
}

void SewingGrid::drawHorizontalLine(QPainter* painter, int y)
{
	QPoint leftP(_viewRect.left(), y);
	QPoint rightP(_viewRect.right(), y);
	painter->setPen(_lPen.linePen);
	painter->drawLine(leftP, rightP);

	drawLabelLine(painter, _viewRect.left(), y, _viewRect.left() + 5, y);
}

void SewingGrid::drawVerticalLine(QPainter* painter, int x)
{
	QPoint upP(x, _viewRect.top());
	QPoint bottomP(x, _viewRect.bottom());
	painter->setPen(_lPen.linePen);
	painter->drawLine(upP, bottomP);

	drawLabelLine(painter, x, _viewRect.bottom() - 5, x, _viewRect.bottom());
}

void SewingGrid::drawLabelLine(QPainter* painter, int x1, int y1, int x2, int y2)
{
	QPoint leftP(x1, y1);
	QPoint rightP(x2, y2);
	painter->setPen(_lPen.labelPen);
	painter->drawLine(leftP, rightP);
}

void SewingGrid::drawLabelX(QPainter* painter, int x, const QString& label)
{
	painter->setPen(_lPen.labelPen);
	painter->drawText(x - Margin, _viewRect.bottom() + 5, 100, 20, Qt::AlignHCenter | Qt::AlignTop, label);
}

void SewingGrid::drawLabelY(QPainter* painter, int y, const QString& label)
{
	int lPos = 0;
	lPos = labelPos(label.toDouble());

	painter->setPen(_lPen.labelPen);
	painter->drawText(_viewRect.left() - lPos, y - 7, Margin - 5, 20, Qt::AlignHCenter | Qt::AlignTop, label);
}

double SewingGrid::coordToPixel(double value)
{
	double result = 0.0;
	switch (_sAxis)
	{
	case sXAxis: result = (value - _axisRange.lower) / _axisRange.size() * _viewRect.width() + _viewRect.left(); break;
	case sYAxis: result = _viewRect.bottom() - (value - _axisRange.lower) / _axisRange.size() * _viewRect.height(); break;
	}

	return result;
}

double SewingGrid::pixelToCoord(double value)
{
	double result = 0.0;
	switch (_sAxis)
	{
	case sXAxis: result = (value - _viewRect.left()) / (double)_viewRect.width() * _axisRange.size() + _axisRange.lower; break;
	case sYAxis: result = (_viewRect.bottom() - value) / (double)_viewRect.height() * _axisRange.size() + _axisRange.lower; break;
	}

	return result;
}

int SewingGrid::labelPos(double label)
{
	int lPos = 33;
	QString strL = QString::number(label).trimmed();

	if (strL.indexOf('e') != -1) return lPos = 50;

	QStringList strList = strL.split(".");
	strList.removeAll("");

	int nCount = 0;
	for (int i = 0; i < strList.count(); i++)
	{
		nCount += getNumOfDigits(strList[i].toInt());
	}

	if (nCount <= 3) lPos = 35;
	if (nCount == 4) lPos = 40;
	if (nCount == 5) lPos = 45;
	if (nCount == 6) lPos = 50;

	return lPos;
}

int SewingGrid::getNumOfDigits(int num)
{
	int count = 0;

	if (num < 0) num = qAbs(num);
	else if (num == 0) num = 1;

	while (num > 0)
	{
		num = num / 10;
		count++;
	}

	return count;
}
