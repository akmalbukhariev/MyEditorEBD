#pragma once

#include <QWidget>

#include "WidgetWokrDesign.h"
#include "ui_WidgetColorTable.h"

class WidgetColorTable : public QWidget
{
	Q_OBJECT

public:
	WidgetColorTable(QWidget *parent = Q_NULLPTR);
	~WidgetColorTable();

private slots:
	void slotWorkDesign(WidgetWokrDesign* wDesign)
	{
		_wDesign = wDesign;
	}

private:
	Ui::WidgetColorTable ui;

	WidgetWokrDesign* _wDesign;
};
