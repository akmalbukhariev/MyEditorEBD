#pragma once

#include <QWidget>

#include "ui_ChenileWidget.h"
#include "CCAbstractWidget.h"

class ChenileWidget : public CCAbstractWidget
{
	Q_OBJECT

public:
	ChenileWidget(QWidget *parent = Q_NULLPTR);
	~ChenileWidget();

private:
	void fillButtonList();

private slots:
	void slotClickButtonNeedle(QPushButton* btn);

private:
	Ui::ChenileWidget ui;
};