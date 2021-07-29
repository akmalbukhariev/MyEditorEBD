#include "WidgetCCTable.h"

WidgetCCTable::WidgetCCTable(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initConnection();
	initModel();
}

WidgetCCTable::~WidgetCCTable()
{
}

void WidgetCCTable::initConnection()
{

}

void WidgetCCTable::initModel()
{
	_tModel = new EBDInfoModel(4, this);
	_tModel->setTableOption(EBDInfoModel::TableOption::ColorTable);
	ui.tView->setModel(_tModel);
	ui.tView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void WidgetCCTable::slotWorkDesign(WidgetWokrDesign* wDesign)
{
	_tModel->setWorkDesign(wDesign);
	_tModel->reset();
}
