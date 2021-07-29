
#include "WidgetSewing.h"
#include "CCTableDialog.h"

#include <QDebug>
#include <qmath.h>
#include <QMouseEvent>
#include <QStylePainter>

WidgetSewing::WidgetSewing(QWidget* parent)
	: QWidget(parent)
{
	initMenu();
	initConnection();
	
	_useMapImage = true;
	_xAxisGrid = NULL;
	_yAxisGrid = NULL;
	_axisPen = QPen(Qt::white, 1);
	 
	_xAxisGrid = new SewingGrid(SAxis::sXAxis);
	_yAxisGrid = new SewingGrid(SAxis::sYAxis);
	_xAxisGrid->setAxisRange(-127, 127);
	_yAxisGrid->setAxisRange(-127, 127);

	_sewing = new Sewing(_xAxisGrid, _yAxisGrid);
	
	_backColor = QColor("#505050");
	setFocusPolicy(Qt::ClickFocus);

	_pointInfoTable = LinePoint();

	_mouseMove = false;
	_clickAxisVisible = true;
	_clickGridVisible = true;
	_clickPointingPoint = false;
	_clickReArrangeObjects = false;
}

WidgetSewing::~WidgetSewing()
{
}

void WidgetSewing::initMenu()
{
	_actionCCTable = new QAction(this);
	_actionCCTable->setText("Manege C/C Table");;
	_menu.addAction(_actionCCTable);
}

void WidgetSewing::initConnection()
{
	connect(_actionCCTable, &QAction::triggered, this, &WidgetSewing::slotClickMenuAction);
}

void WidgetSewing::setVisibleAxis(bool click)
{
	_clickAxisVisible = click;
	replot();
	update();
}

void WidgetSewing::setAxisColor(const QColor& color)
{
	_axisPen = QPen(color);
}

void WidgetSewing::setVisibleGrid(bool click)
{
	_clickGridVisible = click;
	replot();
	update();
}

void WidgetSewing::setPointingPoint(bool click)
{
	_clickPointingPoint = click;
	replot();
	update();
}

void WidgetSewing::setBackgroundColor(const QColor& color)
{
	_backColor = color;
}

void WidgetSewing::setGridStyle(const SewingGrid::LinePen& linePen)
{
	_xAxisGrid->setLineStyle(linePen);
	_yAxisGrid->setLineStyle(linePen);
}

void WidgetSewing::setXAxisRange(double min, double max)
{
	_xAxisGrid->setAxisRange(min, max);
}

void WidgetSewing::setYAxisRange(double min, double max)
{
	_yAxisGrid->setAxisRange(min, max);
}

void WidgetSewing::slotClickMenuAction()
{
	/*CCTableDialog d(_ebdInfo);
	d.exec();*/
}

void WidgetSewing::keyPressEvent(QKeyEvent *event)
{
	int diff = 1;
	switch (event->key())
	{
		case Qt::Key_Up:
			_mouseRelease = QPoint(_mouseRelease.x(), _mouseRelease.y() - diff);
			break;
		case Qt::Key_Down:
			_mouseRelease = QPoint(_mouseRelease.x(), _mouseRelease.y() + diff);
			break;
		case Qt::Key_Left:
			_mouseRelease = QPoint(_mouseRelease.x() - diff, _mouseRelease.y());
			break;
		case Qt::Key_Right:
			_mouseRelease = QPoint(_mouseRelease.x() + diff, _mouseRelease.y());
			break;
	}

	moveDesign(_mouseRelease);

	_mouseUp = true;
	_mouseMove = false;
}

void WidgetSewing::resizeEvent(QResizeEvent* event)
{
	_viewRect = QRect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);
	_xAxisGrid->setViewPort(_viewRect);
	_yAxisGrid->setViewPort(_viewRect);

	replot();
	update();
}

void WidgetSewing::paintEvent(QPaintEvent* event)
{
	QStylePainter painter(this);
	painter.drawPixmap(0, 0, _pixmap);
}

void WidgetSewing::mousePressEvent(QMouseEvent *event)
{
	_mouseUp = false;
	_clickMouse = event->pos();

	_sewing->unActiveAllDesignParts();
	_sewing->unActivateSelectDesign(_clickMouse);
	
	_previousP = event->pos();
	QWidget::mousePressEvent(event);
}

void WidgetSewing::mouseMoveEvent(QMouseEvent* event)
{
	setCursor(Qt::ClosedHandCursor);

	moveDesign(event->pos());

	QWidget::mouseMoveEvent(event);
}

void WidgetSewing::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		/*_menu.popup(mapToGlobal(event->pos()));
		_menu.show();*/
	}
	else
	{
		setCursor(Qt::ArrowCursor);

		_mouseUp = true;
		_mouseMove = false;

		_mouseRelease = event->pos();

		//Control::instance()->setClickDesign(getLinePoint(_mouseRelease));

		replot();
		update();
	}

	QWidget::mouseReleaseEvent(event);
}

void WidgetSewing::wheelEvent(QWheelEvent *event)
{
	double wheelSteps = event->delta() / 120.0;
	double factor = qPow(0.85, wheelSteps);

	_xAxisGrid->scaleRange(factor, _xAxisGrid->pixelToCoord(event->pos().x()));
	_yAxisGrid->scaleRange(factor, _yAxisGrid->pixelToCoord(event->pos().y()));

	_useMapImage = false;

	replot();
	update();
}

QSize WidgetSewing::minimumSizeHint() const
{
	return QSize(6 * Margin, 4 * Margin);
}

QSize WidgetSewing::sizeHint() const
{
	return QSize(12 * Margin, 8 * Margin);
}

void WidgetSewing::replot()
{
	_pixmap = QPixmap(size());
	_pixmap.fill(_backColor);

	QPainter painter(&_pixmap);

	if (_clickAxisVisible) drawXYAxis(&painter);

	if (_clickGridVisible)
	{
		_xAxisGrid->replot(&painter);
		_yAxisGrid->replot(&painter);
	}

	_sewing->drawDesign(&painter);

	bool designChanged = false;
	if (_clickReArrangeObjects)
	{
		if (_mouseMove)
		{
			_sewing->moveDesignPart(_previousP, _clickMouse);
			designChanged = true;
		}

		if (_mouseUp)
			_sewing->drawDesignPartBorder(_mouseRelease, &painter);
	}

	if (designChanged)
		Control::instance()->designDataChanged();

	if (_clickPointingPoint && _pointInfoTable.isValid())
	{
		float x = _xAxisGrid->coordToPixel(_pointInfoTable.startP.x());
		float y = _yAxisGrid->coordToPixel(_pointInfoTable.startP.y());
		x = qRound(x);
		y = qRound(y);

		drawPointLocation(QPoint(x, y), &painter);
	}

	//Control::instance()->updatePixmapInNavigationList(_navigateId, cropDesign());
}

void WidgetSewing::moveDesign(const QPoint& pos)
{
	_mouseUp = false;
	_mouseMove = true;

	if (!_clickReArrangeObjects)
	{
		_xAxisGrid->moveGrid(_previousP, pos);
		_yAxisGrid->moveGrid(_previousP, pos);
	}

	_previousP = pos;

	replot();
	update();

	_clickMouse = _previousP;
}

void WidgetSewing::drawXYAxis(QPainter* painter)
{
	painter->setPen(_axisPen);

	int upLeftX = _viewRect.left();
	int upLeftY = Margin - 5;
	int lowLeftX = _viewRect.left();
	int lowLeftY = _viewRect.bottom();
	int lowRightX = _viewRect.right();

	QPointF upLeft(upLeftX, upLeftY);
	QPointF lowLeft(lowLeftX, lowLeftY);
	QPointF lowReight(lowRightX, lowLeftY);

	QPointF xUpAxis(width() - upLeftX - 5, height() - upLeftY - 10);
	QPointF xDownAxis(width() - upLeftX - 5, lowLeftY + 5);

	/*Coordinate*/
	painter->drawLine(lowLeft, lowReight);
	painter->drawLine(xUpAxis, lowReight);
	painter->drawLine(lowReight, xDownAxis);

	/*Axis*/
	QPointF yLeftAxis(upLeftX - 5, upLeftY + 5);
	QPointF yReightAxis(upLeftX + 5, upLeftY + 5);

	painter->drawLine(upLeft, lowLeft);
	painter->drawLine(yLeftAxis, upLeft);
	painter->drawLine(upLeft, yReightAxis);
}

void WidgetSewing::setClickPointInfo(const LinePoint& point, bool clickTable)
{
	_pointInfoTable = point;
	replot();
}

void WidgetSewing::drawPointLocation(const QPoint& point, QPainter* painter)
{
	//moveCenter(QPoint(x, y));
	painter->setPen(QPen(Qt::red, 1));
	painter->drawLine(point.x(), _viewRect.y(), point.x(), _viewRect.bottom());
	painter->drawLine(_viewRect.x(), point.y(), _viewRect.right(), point.y());
	update();
}

void WidgetSewing::moveCenter(const QPoint& pos)
{
	float cX = qRound((float)(_xAxisGrid->getViewPort().width() / 2));
	float cY = qRound((float)(_yAxisGrid->getViewPort().height() / 2));
	
	if (cX > pos.x())
	{
		for (int i = pos.x() + 1; i <= cX; i++)
		{
			QPoint mPoint = QPoint(i, pos.y());
			moveDesign(mPoint);
		}
	}
	else
	{
		for (int i = pos.x() - 1; i >= cX; i--)
		{
			QPoint mPoint = QPoint(i, pos.y());
			moveDesign(mPoint);
		}
	}

	if (cY > pos.y())
	{
		for (int i = pos.y() + 1; i <= cY; i++)
		{
			QPoint mPoint = QPoint(pos.x(), i);
			moveDesign(mPoint);
		}
	}
	else
	{
		for (int i = pos.y() - 1; i >= cY; i--)
		{
			QPoint mPoint = QPoint(pos.x(), i);
			moveDesign(mPoint);
		}
	}
}

LinePoint WidgetSewing::getLinePoint(const QPoint& point)
{
	const DesignPart& dPart = _sewing->designPart()->getSelectedArea(point);

	LinePoint res = LinePoint();
	for( int i = 0; i < dPart.points.count(); i++)
	{
		const LinePoint& lPoint = dPart.points.at(i);
		if (lPoint.startP == point || lPoint.endP == point)
		{
			res = lPoint;
			break;
		}
	}

	return res;
}

QPixmap WidgetSewing::cropDesign()
{
	return _mapPixmap.copy(_sewing->designPart()->getDesignRect());
}

void WidgetSewing::setRangeXY(int lowX, int upperX, int lowY, int upperY)
{
	_xAxisGrid->setAxisRange(lowX / 10, upperX / 10);
	_yAxisGrid->setAxisRange(lowY / 10, upperY / 10);
}

void WidgetSewing::setEbdInfo(EbdFileInfo* ebdInfo)
{
	_navigateId = ebdInfo->navigateId;
	/*if ((ebdInfo->ebdHeader.ColorSize / 4) == 0)
	{
		_sewing->setStitchColor(_stitchColor);
	}*/
	
	//_sewing->setData(ebdInfo.points);
	_sewing->setData(ebdInfo->dParts);

	_ebdInfo = ebdInfo;
	replot();
}

void WidgetSewing::setStitchColor(const QList<QColor>& cList)
{
	_stitchColor = cList;
}