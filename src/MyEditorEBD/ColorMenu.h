#pragma once

#include <QObject>
#include <QToolBar>
#include <QPushButton>

#include "WidgetWokrDesign.h"

class ColorMenu : public QObject
{
	Q_OBJECT

public:
	ColorMenu(QWidget* source, QObject* parent = 0);
	~ColorMenu();

	//Get color button list.
	const QList<QPushButton*>& GetColorButtonList() const;
	 
	//Set Widget work design.
	void setWorkDesign(WidgetWokrDesign* workDesign);

signals:
	void sigClickButton();

private:
	 
	//Initialize random color 
	void setRandomColor2Buttons();

	//Modified palette color.
	void modifyPaletteColor(int index, const QColor& rgbColor);

	//Clean menu bar.
	void cleanMenuBar();

private slots:

	//All color button click event.
	void slotColorButton();

	//Clean Menu bar.
	void slotCleanMenu();

private :

	QToolBar* _sourceWidget;
	WidgetWokrDesign* _workDesign;

	//Color button list.
	QList<QPushButton*> _btnList;
};
