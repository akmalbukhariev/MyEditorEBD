#pragma once

#include <QWidget>

#include "WidgetWokrDesign.h"
#include "ui_WidgetDesignNavigator.h"

class WidgetDesignNavigator : public QWidget
{
	Q_OBJECT

public:
	WidgetDesignNavigator(QWidget *parent = Q_NULLPTR);
	~WidgetDesignNavigator();

	void addDesign(const QIcon& icon, const QString& iconFileName);
	void removeDesign(const QString& iconFileName);

	void selectItemFile(const QString& iconFileName);

public slots:

	void addItem(WidgetWokrDesign* design);

private:
	Ui::WidgetDesignNavigator ui;
};
