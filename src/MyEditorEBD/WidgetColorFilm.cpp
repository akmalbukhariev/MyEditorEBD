#include "WidgetColorFilm.h"

WidgetColorFilm::WidgetColorFilm(QWidget* parent)
	: QWidget(parent)
{
	_model = Q_NULLPTR;

	ui.setupUi(this);
	initModel();
	initConnection();
}

WidgetColorFilm::~WidgetColorFilm()
{

}

void WidgetColorFilm::initModel()
{
	_model = new ColorFilmModel(3);
	ui.tbView->setModel(_model);

	ui.tbView->verticalHeader()->setVisible(false);
	ui.tbView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void WidgetColorFilm::initConnection()
{
	connect(Control::instance(), &Control::sigCleanAllModels, this, &WidgetColorFilm::slotCleanModel);
}

void WidgetColorFilm::slotWorkDesign(WidgetWokrDesign* wDesign)
{
	_model->setWorkDesign(wDesign);
	_model->reset();
}

void WidgetColorFilm::slotCleanModel()
{
	if (_model != Q_NULLPTR)
		_model->reset();
}
