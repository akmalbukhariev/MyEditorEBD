#include "CCTableDialog.h"
#include "SewingGraphicsView.h"

#include <QEvent>
#include <QDebug>
#include <qmath.h>
#include <qmimedata.h>
#include <QMouseEvent>
#include <QStylePainter>

SewingGraphicsView::SewingGraphicsView(QWidget* parent)
	: QGraphicsView(parent)
{
	setAcceptDrops(true);

	initGridAndSewing();
	initGraphicItems();

	initView();
	initMenu();
	initConnection();
}

SewingGraphicsView::~SewingGraphicsView()
{
}

void SewingGraphicsView::initView()
{
	/*viewport()->setMouseTracking(true);*/
	 
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

	_backColor = QColor("#505050");
	setFocusPolicy(Qt::ClickFocus);

	_useMapImage = true;
	_mouseMove = false;
	_clickAxisVisible = true;
	_clickGridVisible = true;
	_clickPointingPoint = false;
	_clickReArrangeObjects = false;
}

void SewingGraphicsView::initMenu()
{
	_actionCCTable = new QAction(this);
	_actionCCTable->setText("Manege C/C Table");;
	_menu.addAction(_actionCCTable);
}

void SewingGraphicsView::initGraphicItems()
{
	_itemAxis = NULL;
	_itemGrid = NULL;
	_itemPixmap = NULL;
	_itemStitch = NULL;

	_scene = new QGraphicsScene(this);
	_itemPixmap = new QGraphicsPixmapItem();
	_itemGrid = new GridLineItem(_xAxisGrid, _yAxisGrid);
	_itemAxis = new AxisLineItem(&_viewRect, width(), height());
	_itemStitch = new EditStitchesEllipseItem(_xAxisGrid, _yAxisGrid);
	_itemLocation = new PointLocationLineItem(&_viewRect, _xAxisGrid, _yAxisGrid);

	_scene->addItem(_itemPixmap);
	//_scene->addItem(_itemStitch);
	setScene(_scene);
}

void SewingGraphicsView::initGridAndSewing()
{
	_xAxisGrid = NULL;
	_yAxisGrid = NULL;

	_xAxisGrid = new SewingGrid(SAxis::sXAxis);
	_yAxisGrid = new SewingGrid(SAxis::sYAxis);
	_xAxisGrid->setAxisRange(-127, 127);
	_yAxisGrid->setAxisRange(-127, 127);

	_sewing = new Sewing(_xAxisGrid, _yAxisGrid);
}

void SewingGraphicsView::initConnection()
{
	connect(_actionCCTable, &QAction::triggered, this, &SewingGraphicsView::slotClickMenuAction);
}

void SewingGraphicsView::setAxisColor(const QColor& color)
{
	_itemAxis->setAxisColor(color);
}

void SewingGraphicsView::setVisibleAxis(bool click)
{
	if (click)
	{
		_scene->addItem(_itemAxis);
	}
	else if (_scene->items().contains(_itemAxis))
	{
		_scene->removeItem(_itemAxis);
	}

	_clickAxisVisible = click;
	scene()->update();
}

void SewingGraphicsView::setVisibleGrid(bool click)
{
	if (click)
	{
		_scene->addItem(_itemGrid);
	}
	else if (_scene->items().contains(_itemGrid))
	{
		_scene->removeItem(_itemGrid);
	}

	_clickGridVisible = click;
	scene()->update();
}

void SewingGraphicsView::setPointingPoint(bool click)
{
	if (click)
	{
		_scene->addItem(_itemLocation);
	}
	else if (_scene->items().contains(_itemLocation))
	{
		_scene->removeItem(_itemLocation);
	}

	_clickPointingPoint = click;
	_scene->update();
}

void SewingGraphicsView::setBackgroundColor(const QColor& color)
{
	_backColor = color;
}

void SewingGraphicsView::setGridStyle(const SewingGrid::LinePen& linePen)
{
	_xAxisGrid->setLineStyle(linePen);
	_yAxisGrid->setLineStyle(linePen);
}

void SewingGraphicsView::setXAxisRange(double min, double max)
{
	_xAxisGrid->setAxisRange(min, max);
}

void SewingGraphicsView::setYAxisRange(double min, double max)
{
	_yAxisGrid->setAxisRange(min, max);
}

void SewingGraphicsView::slotClickMenuAction()
{
	/*CCTableDialog d(_ebdInfo);
	d.exec();*/
}

void SewingGraphicsView::keyPressEvent(QKeyEvent *event)
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

void SewingGraphicsView::resizeEvent(QResizeEvent* event)
{
	_viewRect = QRect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);
	_xAxisGrid->setViewPort(_viewRect);
	_yAxisGrid->setViewPort(_viewRect);

	if (_itemAxis != NULL)
		_itemAxis->updateSize(width(), height());

	replot();
	update();
}

void SewingGraphicsView::resizeView()
{
	resetTransform();
	QRectF sceneR = sceneRect();
	if (this->width() < sceneR.width() || this->height() < sceneR.height())
	{
		float fWidth = this->width() / sceneR.width();
		float fHeight = (this->height()) / sceneR.height();
		float fMin;

		fMin = (fWidth > fHeight) ? fHeight : fWidth;

		scale(fMin, fMin);
	}
}

void SewingGraphicsView::dragEnterEvent(QDragEnterEvent* event)
{
	event->accept();
}

void SewingGraphicsView::dragMoveEvent(QDragMoveEvent* event)
{
	event->accept();
}

void SewingGraphicsView::dropEvent(QDropEvent* event)
{
	QList<QUrl> urls = event->mimeData()->urls();

	if (urls.count() > 0)
	{
		QString fileName = urls.first().toLocalFile();
		Control::instance()->setFileHasDropped(fileName);
	}
}

void SewingGraphicsView::mousePressEvent(QMouseEvent* event)
{
	_mouseUp = false;
	_clickMouse = event->pos();

	_sewing->unActiveAllDesignParts();
	_sewing->unActivateSelectDesign(_clickMouse);

	_previousP = event->pos();
	QGraphicsView::mousePressEvent(event);
}

void SewingGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
	//if (event->button() == Qt::LeftButton)
	{
		if (_clickEditStitches)
		{
			_itemStitch->setPointInfo(getLinePoint(event->pos()));
			scene()->update();
		}
		else
		{
			setCursor(Qt::ClosedHandCursor);

			moveDesign(event->pos());
		}
	}
	QGraphicsView::mouseMoveEvent(event);
}

void SewingGraphicsView::mouseReleaseEvent(QMouseEvent *event)
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

	QGraphicsView::mouseReleaseEvent(event);
}

void SewingGraphicsView::wheelEvent(QWheelEvent *event)
{
	double wheelSteps = event->delta() / 120.0;
	double factor = qPow(0.85, wheelSteps);

	_xAxisGrid->scaleRange(factor, _xAxisGrid->pixelToCoord(event->pos().x()));
	_yAxisGrid->scaleRange(factor, _yAxisGrid->pixelToCoord(event->pos().y()));

	_useMapImage = false;

	replot();
	update();
}

QSize SewingGraphicsView::minimumSizeHint() const
{
	return QSize(6 * Margin, 4 * Margin);
}

QSize SewingGraphicsView::sizeHint() const
{
	return QSize(12 * Margin, 8 * Margin);
}

void SewingGraphicsView::replot()
{
	_pixmap = QPixmap(size());
	_pixmap.fill(_backColor);

	QPainter painter(&_pixmap); 

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

	_itemPixmap->setPos(0, 0);
	_itemPixmap->setPixmap(_pixmap);
	
	_mapPixmap = cropDesign();
	Control::instance()->designDataChanged();
}

void SewingGraphicsView::moveDesign(const QPoint& pos)
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

void SewingGraphicsView::setClickPointInfo(const LinePoint& point, bool clickTable)
{
	if (_clickPointingPoint )
	{
		_itemLocation->setPointInfo(point);
	}

	_scene->update();
}
 
void SewingGraphicsView::moveCenter(const QPoint& pos)
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

LinePoint SewingGraphicsView::getLinePoint(const QPoint& point)
{
	const DesignPart& dPart = _sewing->designPart()->getSelectedArea(point);

	LinePoint res = LinePoint();
	for (int i = 0; i < dPart.points.count(); i++)
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

QPixmap SewingGraphicsView::cropDesign()
{
	return _pixmap.copy(_sewing->designPart()->getDesignRect());
}

void SewingGraphicsView::setRangeXY(int lowX, int upperX, int lowY, int upperY)
{
	_xAxisGrid->setAxisRange(lowX / 10, upperX / 10);
	_yAxisGrid->setAxisRange(lowY / 10, upperY / 10);
}

void SewingGraphicsView::setEbdInfo(EbdFileInfo* ebdInfo)
{
	_navigateId = ebdInfo->navigateId;
	_sewing->setData(ebdInfo->dParts);

	_ebdInfo = ebdInfo;
	replot();
}

void SewingGraphicsView::setStitchColor(const QList<QColor>& cList)
{
	_stitchColor = cList;
}