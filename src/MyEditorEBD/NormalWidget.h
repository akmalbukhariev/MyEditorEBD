#pragma once

#include <QWidget>

#include "ui_NormalWidget.h"
#include "CCAbstractWidget.h"

class NormalWidget : public CCAbstractWidget
{
	Q_OBJECT

public:
	NormalWidget(QWidget* parent = Q_NULLPTR);
	~NormalWidget();

private:
	void fillButtonList();

private slots:
	void slotClickButtonNeedle(QPushButton* btn);
	void slotClickButtonARM(QPushButton* btn);

private:
	Ui::NormalWidget ui; 
};
