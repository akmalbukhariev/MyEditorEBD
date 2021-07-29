#pragma once

#include <QMap>
#include <QPainter>

#include "CommonDef.h"

using namespace CommonDef;

class SewingGrid  
{
public:

	SewingGrid(SAxis sAxis);
	SewingGrid();
	~SewingGrid();

	/*Set a range of axis.*/
	void setAxisRange(double min, double max);

	/*Add an axis label.*/
	void addAxisLabel(double position, QString label);

	/*Scale the mouse points.*/
	void scaleRange(double factor, double center);

	/*Refresh the grid layer.*/
	void replot(QPainter* painter);

	/*Set a pen of lines.*/
	void setLinePen(const QPen& linePen, const QPen& labelPen);

	/*Modify the Axis range while mouse is moving.*/
	void moveGrid(const QPoint& startPoint, const QPoint& endPoint);

	/*Set a iewport.*/
	void setViewPort(const QRect& viewRect) { _viewRect = viewRect; }

	/*Get a viewport*/
	QRect getViewPort() const { return _viewRect; }

	/*Convert pixel to coordinate.*/
	double pixelToCoord(double value);

	/*Convert coordinate to pixel.*/
	double coordToPixel(double value);

	/*Get axis xoordinate numbers.*/
	SAxisRange getAxisRange() const { return _axisRange; }

	/*All lines pens*/
	struct LinePen
	{
		QPen linePen;  // !For the line.
		QPen labelPen; // !For the label.

		LinePen()
		{
			linePen.setColor(Qt::gray);
			linePen.setStyle(Qt::DotLine);
			labelPen = QPen(Qt::white, 1);
		}
	};

	/*Set line style.*/
	void setLineStyle(const SewingGrid::LinePen& linePen)
	{
		_lPen = linePen;
	}

private:

	/*Draw the horizontal line.*/
	void drawHorizontalLine(QPainter* painter, int y);

	/*Draw the vertical line.*/
	void drawVerticalLine(QPainter* painter, int x);

	/*Draw the label line and paint it.*/
	void drawLabelLine(QPainter* painter, int x1, int y1, int x2, int y2);

	/*Draw the label text.*/
	void drawLabelX(QPainter* painter, int x, const QString& label);
	void drawLabelY(QPainter* painter, int y, const QString& label);

	/*Check a label number.*/
	int labelPos(double label);
	int getNumOfDigits(int num);

private:

	QVector< double > _ticks;
	QMap< double, QString > _lList;

	SAxis _sAxis;

	LinePen _lPen;
	QRect _viewRect;
	SAxisRange _axisRange;
};
