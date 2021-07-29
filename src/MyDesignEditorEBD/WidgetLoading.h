#pragma once

#include <QDialog>
#include "ui_WidgetLoading.h"

class WidgetLoading : public QDialog
{
	Q_OBJECT

public:
	WidgetLoading(QWidget* parent = Q_NULLPTR);
	~WidgetLoading();

private:
	void initUI();

protected:
	void showEvent(QShowEvent* event) override;

private:
	Ui::WidgetLoading ui;
};
