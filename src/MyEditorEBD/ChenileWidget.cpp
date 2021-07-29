#include "ChenileWidget.h"

ChenileWidget::ChenileWidget(QWidget* parent)
	: CCAbstractWidget(parent)
{
	ui.setupUi(this);
	//_className = "ChenileWidget";
	_isChenile = true;

	fillButtonList();
	initConnection();

	connect(this, &CCAbstractWidget::sigSendClickButton, this, &ChenileWidget::slotClickButtonNeedle);
}

ChenileWidget::~ChenileWidget()
{

}

void ChenileWidget::fillButtonList()
{
	const char* prName = "SetColor";

	ui.pB_L1_->setProperty(prName, true);
	ui.pB_L2_->setProperty(prName, true);
	ui.pB_L3_->setProperty(prName, true);
	ui.pB_L4_->setProperty(prName, true);
	ui.pB_L5_->setProperty(prName, true);
	ui.pB_L6_->setProperty(prName, true);
	ui.pB_C1_->setProperty(prName, true);
	ui.pB_C2_->setProperty(prName, true);
	ui.pB_C3_->setProperty(prName, true);
	ui.pB_C4_->setProperty(prName, true);
	ui.pB_C5_->setProperty(prName, true);
	ui.pB_C6_->setProperty(prName, true);

	ui.pB_L1->setProperty(prName, false);
	ui.pB_L2->setProperty(prName, false);
	ui.pB_L3->setProperty(prName, false);
	ui.pB_L4->setProperty(prName, false);
	ui.pB_L5->setProperty(prName, false);
	ui.pB_L6->setProperty(prName, false);
	ui.pB_C1->setProperty(prName, false);
	ui.pB_C2->setProperty(prName, false);
	ui.pB_C3->setProperty(prName, false);
	ui.pB_C4->setProperty(prName, false);
	ui.pB_C5->setProperty(prName, false);
	ui.pB_C6->setProperty(prName, false);
	 
	_btnList.append(ui.pB_L1_);
	_btnList.append(ui.pB_L2_);
	_btnList.append(ui.pB_L3_);
	_btnList.append(ui.pB_L4_);
	_btnList.append(ui.pB_L5_);
	_btnList.append(ui.pB_L6_);
	_btnList.append(ui.pB_C1_);
	_btnList.append(ui.pB_C2_);
	_btnList.append(ui.pB_C3_);
	_btnList.append(ui.pB_C4_);
	_btnList.append(ui.pB_C5_);
	_btnList.append(ui.pB_C6_);

	_btnList.append(ui.pB_L1);
	_btnList.append(ui.pB_L2);
	_btnList.append(ui.pB_L3);
	_btnList.append(ui.pB_L4);
	_btnList.append(ui.pB_L5);
	_btnList.append(ui.pB_L6);
	_btnList.append(ui.pB_C1);
	_btnList.append(ui.pB_C2);
	_btnList.append(ui.pB_C3);
	_btnList.append(ui.pB_C4);
	_btnList.append(ui.pB_C5);
	_btnList.append(ui.pB_C6);
}

void ChenileWidget::slotClickButtonNeedle(QPushButton* btn)
{
	quint16 Chenille_Loop = 0x0080;
	quint16 Chenille_Chain = 0x0100;

	NeedleSet inputData;
	if (ui.pB_L1 == btn)
	{
		inputData.Needle = Chenille_Loop | 0x01;// 0x101;
		inputData.Group = 0;
	}
	else if (ui.pB_L2 == btn)
	{
		inputData.Needle = Chenille_Loop | 0x02;// 0x102;
		inputData.Group = 0;
	}
	else if (ui.pB_L3 == btn)
	{
		inputData.Needle = Chenille_Loop | 0x03;// 0x103;
		inputData.Group = 0;
	}
	else if (ui.pB_L4 == btn)
	{
		inputData.Needle = Chenille_Loop | 0x04;// 0x104;
		inputData.Group = 0;
	}
	else if (ui.pB_L5 == btn)
	{
		inputData.Needle = Chenille_Loop | 0x05;// 0x105;
		inputData.Group = 0;
	}
	else if (ui.pB_L6 == btn)
	{
		inputData.Needle = Chenille_Loop | 0x06;// 0x106;
		inputData.Group = 0;
	}
	else if (ui.pB_C1 == btn)
	{
		inputData.Needle = Chenille_Chain | 0x01;// 0x201;
		inputData.Group = 0;
	}
	else if (ui.pB_C2 == btn)
	{
		inputData.Needle = Chenille_Chain | 0x02;//0x202;
		inputData.Group = 0;
	}
	else if (ui.pB_C3 == btn)
	{
		inputData.Needle = Chenille_Chain | 0x03;//0x203;
		inputData.Group = 0;
	}
	else if (ui.pB_C4 == btn)
	{
		inputData.Needle = Chenille_Chain | 0x04;//0x204;
		inputData.Group = 0;
	}
	else if (ui.pB_C5 == btn)
	{
		inputData.Needle = Chenille_Chain | 0x05;//0x205;
		inputData.Group = 0;
	}
	else if (ui.pB_C6 == btn)
	{
		inputData.Needle = Chenille_Chain | 0x06;//0x206;
		inputData.Group = 0;
	}

	modifyNeedleSetWithOffsetAndStop(inputData);
	setNeedleSetToModel(inputData);
}