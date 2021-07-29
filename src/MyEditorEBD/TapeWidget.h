#pragma once

#include <QWidget>

#include "ui_TapeWidget.h"
#include "CCAbstractWidget.h"

class TapeWidget : public CCAbstractWidget
{
	Q_OBJECT

public:
	TapeWidget(QWidget* parent = Q_NULLPTR);
	~TapeWidget();

private:
	void fillButtonList();

private slots:
	void slotClickButtonNeedle(QPushButton* btn);

private:
	Ui::TapeWidget ui;
};
