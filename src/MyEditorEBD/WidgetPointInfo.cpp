#include "WidgetPointInfo.h"

WidgetPointInfo::WidgetPointInfo(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initConnection();
	initModel();
}

WidgetPointInfo::~WidgetPointInfo()
{

}

void WidgetPointInfo::initConnection()
{
	connect(Control::instance(), &Control::sigCleanAllModels, this, &WidgetPointInfo::slotCleanModel);
}

void WidgetPointInfo::initModel()
{
	_tModel = new EBDInfoModel(3, this);
	_tModel->setTableOption(EBDInfoModel::TableOption::PointTable);
	ui.tView->setModel(_tModel);
	ui.tView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void WidgetPointInfo::slotWorkDesign(WidgetWokrDesign* wDesign)
{
	_tModel->setWorkDesign(wDesign);
	_tModel->reset();
}

void WidgetPointInfo::slotUpdateScroll()
{
	WidgetWokrDesign* wDesign = _tModel->getWorkDesign();
	if (wDesign == nullptr) return;

	ui.tView->moveScroll(wDesign->getRowOfMovingPart());
}

void WidgetPointInfo::slotCleanModel()
{
	if (_tModel != Q_NULLPTR)
		_tModel->reset();
}