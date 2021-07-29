#pragma once
#include "EBDInfoModel.h"

#include <QTableView>

class PointTableView : public QTableView
{
	Q_OBJECT

public:
	PointTableView(QWidget *parent);
	~PointTableView();

	//Move the scroll.
	void moveScroll(int row);

private:
	void initConnection();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
	void slotClickDesign(const LinePoint& point);
};
