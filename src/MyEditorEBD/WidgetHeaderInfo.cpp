#include "WidgetHeaderInfo.h"

WidgetHeaderInfo::WidgetHeaderInfo(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initConnection();
	initModel();
}

WidgetHeaderInfo::~WidgetHeaderInfo()
{
	 
}

void WidgetHeaderInfo::initConnection()
{
	connect(Control::instance(), &Control::sigCleanAllModels, this, &WidgetHeaderInfo::slotCleanModel);
}

void WidgetHeaderInfo::initModel()
{
	_tModel = new EBDInfoModel(2, this);
	_tModel->setTableOption(EBDInfoModel::TableOption::HeaderTable);
	ui.tView->setModel(_tModel);
	ui.tView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void WidgetHeaderInfo::slotWorkDesign(WidgetWokrDesign* wDesign)
{
	_tModel->setWorkDesign(wDesign);
	_tModel->reset();
}

void WidgetHeaderInfo::slotCleanModel()
{
	if (_tModel != Q_NULLPTR)
		_tModel->reset();
}