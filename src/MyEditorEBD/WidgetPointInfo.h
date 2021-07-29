#pragma once

#include <QWidget>

#include "EBDInfoModel.h"
#include "WidgetWokrDesign.h"
#include "ui_WidgetPointInfo.h"

class WidgetPointInfo : public QWidget
{
	Q_OBJECT

public:
	WidgetPointInfo(QWidget* parent = Q_NULLPTR);
	~WidgetPointInfo();

public slots:
	void slotWorkDesign(WidgetWokrDesign* wDesign);
	void slotUpdateScroll();
	void slotCleanModel();
private:
	void initConnection();
	void initModel();

private:
	Ui::WidgetPointInfo ui;

	EBDInfoModel* _tModel;
};
