#pragma once

#include <QWidget>

#include "ColorFilmModel.h"
#include "WidgetWokrDesign.h"
#include "ui_WidgetColorFilm.h"

class WidgetColorFilm : public QWidget
{
	Q_OBJECT

public:
	WidgetColorFilm(QWidget* parent = Q_NULLPTR);
	~WidgetColorFilm();

public slots:
	void slotWorkDesign(WidgetWokrDesign* wDesign);
	void slotCleanModel();

	void refreshModel()
	{
		_model->reset();
	}

private:
	void initModel();
	void initConnection();

private:
	Ui::WidgetColorFilm ui;

	ColorFilmModel* _model;
};
