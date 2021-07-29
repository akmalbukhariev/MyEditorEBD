#pragma once

#include <QObject>

#include <ThreadLoading.h>
#include "WidgetLoading.h"

class Control : public QObject
{
	Q_OBJECT

public:
	Control();
	~Control();

	static Control* instance();

	void showLoading(QWidget* parent);

	//Cloae loading process.
	void closeLoading();

private:
	static Control* _self;

	WidgetLoading* _wLoading;
	ThreadLoading* _thLoading;
};