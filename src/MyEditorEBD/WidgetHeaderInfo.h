#pragma once

#include <QWidget>

#include "EBDInfoModel.h"
#include "WidgetWokrDesign.h"
#include "ui_WidgetHeaderInfo.h"

class WidgetHeaderInfo : public QWidget
{
	Q_OBJECT

public:
	WidgetHeaderInfo(QWidget *parent = Q_NULLPTR);
	~WidgetHeaderInfo();

public slots:
	void slotWorkDesign(WidgetWokrDesign* wDesign);
	void slotCleanModel();

private:
	void initConnection();
	void initModel();

private:
	Ui::WidgetHeaderInfo ui;

	EBDInfoModel* _tModel;
};
