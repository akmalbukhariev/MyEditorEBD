#pragma once

#include <QWidget>
#include "ui_WidgetSequenceViewer.h"

class WidgetSequenceViewer : public QWidget
{
	Q_OBJECT

public:
	WidgetSequenceViewer(QWidget *parent = Q_NULLPTR);
	~WidgetSequenceViewer();

private:
	Ui::WidgetSequenceViewer ui;
};
