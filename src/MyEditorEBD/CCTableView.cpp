#include "CCTableView.h"

#include <QScrollBar>
#include <QMouseEvent>
#include <QHeaderView>

CCTableView::CCTableView(QWidget *parent)
	: QTableView(parent)
{
	_curIndex = 0;
	_ccDelegate = new CCTableItemDelegate(this);
	setItemDelegate(_ccDelegate);

	initMenu();
	initConnection();
}

CCTableView::~CCTableView()
{
}

void CCTableView::initView()
{
	QHeaderView *verticalH = verticalHeader();
	verticalH->setSectionResizeMode(QHeaderView::Fixed);
	verticalH->setDefaultSectionSize(40);

	selectRow(0);
	setColumnWidth(0, 50);
	setColumnWidth(1, 47);
	setColumnWidth(2, 50);
	setColumnWidth(3, 58);
	setColumnWidth(4, 58);

	//setSelectionBehavior(QAbstractItemView::SelectRows);
	//setSelectionMode(QAbstractItemView::SingleSelection);

	//setSelectionBehavior(QAbstractItemView::SelectColumns);
	//setSelectionMode(QAbstractItemView::SingleSelection);
}

void CCTableView::initMenu()
{
	_actionOffset = new QAction(QIcon("Resources/btn_O_nor.png"), "Add offset");
	_actionStop = new QAction(QIcon("Resources/btn_S_sel.png"), "Add stop");
	_menu.addAction(_actionOffset);
	_menu.addAction(_actionStop);
}

void CCTableView::initConnection()
{
	connect(_actionOffset, &QAction::triggered, this, &CCTableView::slotClickMenu);
	connect(_actionStop, &QAction::triggered, this, &CCTableView::slotClickMenu);
}

void CCTableView::paintEvent(QPaintEvent* event)
{
	QTableView::paintEvent(event);
	QPainter painter(viewport());
	QPen pen;
	QFont fontText;
	fontText.setPointSize(15);
	pen.setColor(QColor(128, 128, 255, 128));
	pen.setWidth(6);
	painter.setFont(fontText);
	painter.setPen(pen);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QPoint center = viewport()->rect().center();

	QString strMessage;
	if (model()->rowCount() == 0)
		strMessage = "No Color Info";

	painter.drawText(viewport()->rect(), Qt::AlignCenter, strMessage);
}

void CCTableView::mouseReleaseEvent(QMouseEvent* event)
{
	QModelIndex index = indexAt(event->pos());
	_row = index.row();

	if (event->button() == Qt::RightButton)
	{
		if (ccTableModel()->getData()[index.row()].Needle != 0)
		{
			_menu.popup(event->screenPos().toPoint());
			_menu.show();
		}
	}

	QTableView::mouseReleaseEvent(event);
}

void CCTableView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
	QModelIndex index = currentIndex();
	if (!index.isValid()) return;

	_ccDelegate->useThis(true);

	if (index.row() > 0 && ccTableModel()->getData()[index.row()].Needle == 0)
	{
		if (ccTableModel()->getData()[index.row()].Needle == 0)
		{
			selectRow(_curIndex);
			_ccDelegate->useThis(false);
			return;
		}
	}
	
	_curIndex =  selectionModel()->currentIndex().row();
	selectRow(_curIndex);

	//verticalScrollBar()->setValue(_curIndex);

	QTableView::selectionChanged(selected, deselected);
}

void CCTableView::slotClickMenu()
{
	quint16 NT_Offset = 0x8000;
	quint16 NT_Stop = 0x4000;

	CCTableModel* ccModel = qobject_cast<CCTableModel*>(model());

	if (_actionOffset == sender())
	{
		ccModel->getData()[_row].Needle ^= NT_Offset;

		int temp = ccModel->getData()[_row].Needle & (NT_Offset | NT_Stop);
		int TValue = (char)(temp >> 14);
		if (TValue == 3)
		{
			ccModel->getData()[_row].Needle &= 0xbfff;
		}
	}
	else if (_actionStop == sender())
	{
		ccModel->getData()[_row].Needle ^= NT_Stop;

		int temp = ccModel->getData()[_row].Needle & (NT_Offset | NT_Stop);
		int TValue = (char)(temp >> 14);
		if (TValue == 3)
		{
			ccModel->getData()[_row].Needle &= 0x7fff;
		}
	}

	ccModel->setOptionRow(_row);
	clearSelection();
	selectRow(_row);
}

CCTableModel* CCTableView::ccTableModel()
{
	return qobject_cast<CCTableModel*>(model());
}