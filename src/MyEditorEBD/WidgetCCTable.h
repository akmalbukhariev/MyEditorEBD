#pragma once

#include <QWidget>

#include "EBDInfoModel.h"
#include "WidgetWokrDesign.h"
#include "ui_WidgetCCTable.h"

class WidgetCCTable : public QWidget
{
	Q_OBJECT

public:
	WidgetCCTable(QWidget *parent = Q_NULLPTR);
	~WidgetCCTable();

public slots:
	void slotWorkDesign(WidgetWokrDesign* wDesign);

private:
	void initConnection();
	void initModel();

private:
	Ui::WidgetCCTable ui;

	EBDInfoModel* _tModel;
};
