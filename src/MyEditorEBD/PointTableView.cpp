#include "PointTableView.h"

#include <QScrollBar>
#include <QMouseEvent>

PointTableView::PointTableView(QWidget *parent)
	: QTableView(parent)
{
	//setSelectionMode(SelectionMode::);
	//setSortingEnabled(true);
	setSelectionBehavior(SelectionBehavior::SelectRows);

	initConnection();
}

PointTableView::~PointTableView()
{
	
}

void PointTableView::initConnection()
{
	connect(Control::instance(), &Control::sigClickDesign, this, &PointTableView::slotClickDesign);
}

void PointTableView::mousePressEvent(QMouseEvent* event)
{
	QTableView::mousePressEvent(event);
}

void PointTableView::mouseReleaseEvent(QMouseEvent* event)
{
	int row = currentIndex().row();
	
	EBDInfoModel* tModel = qobject_cast<EBDInfoModel*>(model());
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		Control::instance()->setClickPointInfoTable(tModel->getData(row));
	}

	QTableView::mouseReleaseEvent(event);
}

void PointTableView::moveScroll(int row)
{
	verticalScrollBar()->setValue(row);
}

void PointTableView::slotClickDesign(const LinePoint& point)
{
	
}