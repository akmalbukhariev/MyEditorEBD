#pragma once

#include <QMenu>
#include <QTableView>

#include "CommonDef.h"
#include "CCTableItemDelegate.h"

using namespace CommonDef;

class CCTableView : public QTableView
{
	Q_OBJECT

public:
	CCTableView(QWidget *parent);
	~CCTableView();

	void initView();

	void setCurrentIndex(int row)
	{
		_curIndex = row;
	}

	//Get a CC table model.
	CCTableModel* ccTableModel();

protected:
	void paintEvent(QPaintEvent* event);
	void mouseReleaseEvent(QMouseEvent* event) override;
	void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;

private:
	void initMenu();
	void initConnection();

private slots:
	void slotClickMenu();

private:
	int _row;
	int _curIndex;

	QMenu _menu;
	QAction* _actionOffset;
	QAction* _actionStop;

	CCTableItemDelegate* _ccDelegate;
};
