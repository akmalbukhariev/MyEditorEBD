#include "TapeWidget.h"

TapeWidget::TapeWidget(QWidget *parent)
	: CCAbstractWidget(parent)
{
	ui.setupUi(this);
	//_className = "TapeWidget";
	fillButtonList();
	initConnection();

	connect(this, &CCAbstractWidget::sigSendClickButton, this, &TapeWidget::slotClickButtonNeedle);
}

TapeWidget::~TapeWidget()
{
}

void TapeWidget::fillButtonList()
{
	const char* prName = "SetColor";

	ui.pBNormal->setProperty(prName,   false);  
	ui.pB_R_Frill->setProperty(prName, false);
	ui.pB_R_Coil->setProperty(prName,  false); 
	ui.pB_R_Tape->setProperty(prName,  false); 
	ui.pB_F_Frill->setProperty(prName, false);
	ui.pB_F_Coil->setProperty(prName,  false); 
	ui.pB_F_Tape->setProperty(prName,  false); 
	ui.pB_Z1->setProperty(prName, false);
	ui.pB_Z2->setProperty(prName, false);
	ui.pB_Z3->setProperty(prName, false);
	ui.pB_Z4->setProperty(prName, false);
	ui.pB_Z5->setProperty(prName, false);
	ui.pB_Z6->setProperty(prName, false);

	_btnList.append(ui.pBNormal);
	_btnList.append(ui.pB_R_Frill);
	_btnList.append(ui.pB_R_Coil);
	_btnList.append(ui.pB_R_Tape);
	_btnList.append(ui.pB_F_Frill);
	_btnList.append(ui.pB_F_Coil);
	_btnList.append(ui.pB_F_Tape);
	_btnList.append(ui.pB_Z1);
	_btnList.append(ui.pB_Z2);
	_btnList.append(ui.pB_Z3);
	_btnList.append(ui.pB_Z4);
	_btnList.append(ui.pB_Z5);
	_btnList.append(ui.pB_Z6);
}

void TapeWidget::slotClickButtonNeedle(QPushButton* btn)
{
	quint16 NT_TapingBobbin = 0x0800;

	quint16 Taping_Normal = 0x0200;
	quint16 Taping_Tape = 0x0280;
	quint16 Taping_Coil = 0x0300;
	quint16 Taping_Frill = 0x0380;
	quint16 Zigzag1 = 0x0400;
	quint16 Zigzag2 = 0x0480;
	quint16 Zigzag3 = 0x0500;
	quint16 Zigzag4 = 0x0580;
	quint16 Zigzag5 = 0x0600;
	quint16 Zigzag6 = 0x0680;

	NeedleSet inputData;
	if (ui.pB_F_Tape == btn)
	{
		inputData.Needle = Taping_Tape | 0x01;//0x0501;
		inputData.Group = 0;
	}
	else if (ui.pB_R_Tape == btn)
	{
		inputData.Needle = NT_TapingBobbin | Taping_Tape | 0x01;//0x1501;
		inputData.Group = 0;
	}
	else if (ui.pB_F_Coil == btn)
	{
		inputData.Needle = Taping_Coil | 0x01;//0x0601;
		inputData.Group = 0;
	}
	else if (ui.pB_R_Coil == btn)
	{
		inputData.Needle = NT_TapingBobbin | Taping_Coil | 0x01;// 0x1601;
		inputData.Group = 0;
	}
	else if (ui.pB_F_Frill == btn)
	{
		inputData.Needle = Taping_Frill | 0x01;// 0x0701;
		inputData.Group = 0;
	}
	else if (ui.pB_R_Frill == btn)
	{
		inputData.Needle = NT_TapingBobbin | Taping_Frill | 0x01;// 0x1701;
		inputData.Group = 0;
	}
	else if (ui.pBNormal == btn)
	{
		inputData.Needle = Taping_Normal | 0x01;// 0x0401;
		inputData.Group = 0;
	}
	else if (ui.pB_Z1 == btn)
	{
		inputData.Needle = Zigzag1 | 0x01;// 0x0801;
		inputData.Group = 0;
	}
	else if (ui.pB_Z2 == btn)
	{
		inputData.Needle = Zigzag2 | 0x01;//0x0901;
		inputData.Group = 0;
	}
	else if (ui.pB_Z3 == btn)
	{
		inputData.Needle = Zigzag3 | 0x01;//0x0A01;
		inputData.Group = 0;
	}
	else if (ui.pB_Z4 == btn)
	{
		inputData.Needle = Zigzag4 | 0x01;//0x0B01;
		inputData.Group = 0;
	}
	else if (ui.pB_Z5 == btn)
	{
		inputData.Needle = Zigzag5 | 0x01;//0x0C01;
		inputData.Group = 0;
	}
	else if (ui.pB_Z6 == btn)
	{
		inputData.Needle = Zigzag6 | 0x01;//0x0D01;
		inputData.Group = 0;
	}

	modifyNeedleSetWithOffsetAndStop(inputData);
	setNeedleSetToModel(inputData);
}