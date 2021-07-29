#pragma once

#include <QMenu>
#include <QWidget>

#include "Sewing.h"

class WidgetSewing : public QWidget
{
	Q_OBJECT

public:
	WidgetSewing(QWidget* parent = Q_NULLPTR);
	~WidgetSewing();

	//Get a pixmap.
	const QPixmap& getDesignMap() const
	{
		return _pixmap;
	}

	//Get an x axis grid.
	SewingGrid* xAxisGrid() const { return _xAxisGrid; }

	//Get an y axis grid.
	SewingGrid* yAxisGrid() const { return _yAxisGrid; }

	//Set Axis color.
	void setAxisColor(const QColor& color);

	//Set a backgroud color.
	void setBackgroundColor(const QColor& color);

	//Set axis style.
	void setGridStyle(const SewingGrid::LinePen& linePen);

	//Set X axis range.
	void setXAxisRange(double min, double max);

	//Set Y axis range.
	void setYAxisRange(double min, double max);

	//Refresh a pixmap.
	void replot();

	//Set ebd file info.
	void setEbdInfo(EbdFileInfo* ebdInfo);
	 
	//Set stitch color.
	void setStitchColor(const QList<QColor>& cList);

	//Set a range of axis.
	void setRangeXY(int lowX, int upperX, int lowY, int upperY);

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	//Set click point info.
	void setClickPointInfo(const LinePoint& point, bool clickTable);

#pragma region Properies

	//Make a visible axis.
	void setVisibleAxis(bool click);

	//Make a visible grid.
	void setVisibleGrid(bool click);

	//Click design part.
	void setReArrangeObjects(bool click)
	{
		_clickReArrangeObjects = click;
	}

	//Click Edit stitches.
	void setEditStitches(bool click)
	{
		_clickEditStitches = click;
	}

	//Set pointing when user click on pointInfo table.
	void setPointingPoint(bool click);

	//Make a visible axis.
	bool getVisibleAxis() const
	{
		return _clickAxisVisible;
	}

	//Make a visible grid.
	bool getVisibleGrid() const
	{
		return _clickGridVisible;
	}

	//Click design part.
	bool getReArrangeObjects() const
	{
		return _clickReArrangeObjects;
	}

	//Click Edit stitches.
	bool getEditStitches() const
	{
		return _clickEditStitches;
	}
	  
#pragma endregion

protected:

	//bool event(QEvent *event) override;

	void wheelEvent(QWheelEvent* event);
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

	void keyPressEvent(QKeyEvent* event);
	//void keyReleaseEvent(QKeyEvent* event);

private:

	//Initialize menu.
	void initMenu();

	//Initialize connection.
	void initConnection();

	//Move design
	void moveDesign(const QPoint& pos);

	//Draw X/Y Axis.
	void drawXYAxis(QPainter* painter);

	//Find a LinePoint.
	LinePoint getLinePoint(const QPoint& point);

	//Crop the design image from pixmap.
	QPixmap cropDesign();

	//Draw the point location.
	void drawPointLocation(const QPoint& point, QPainter* painter);

	//Move to center of the design.
	void moveCenter(const QPoint& pos);

private slots:
	void slotClickMenuAction();

private:

	bool _mouseUp;
	bool _mouseMove;
	bool _useMapImage;
	
	bool _clickAxisVisible;
	bool _clickGridVisible;
	bool _clickEditStitches;
	bool _clickPointingPoint;
	bool _clickReArrangeObjects;

	int _nWidth;
	int _nHeight;
	int _navigateId;

	QMenu _menu;
	QAction* _actionCCTable;

	EbdFileInfo* _ebdInfo;

	QList<QColor> _stitchColor;

	QColor _backColor;

	QPixmap _pixmap;
	QPixmap _curPixmap;
	QPixmap _mapPixmap;

	QPoint _clickMouse;
	QPoint _previousP;
	QPoint _mouseRelease;

	QPen _axisPen;  //!For the axis.

	LinePoint _pointInfoTable;

	QRect _viewRect;
	Sewing* _sewing;

	SewingGrid* _xAxisGrid;
	SewingGrid* _yAxisGrid;
};
