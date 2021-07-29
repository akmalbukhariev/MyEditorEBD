#include "NormalWidget.h"

NormalWidget::NormalWidget(QWidget* parent)
	: CCAbstractWidget(parent)
{
	ui.setupUi(this);
	//_className = "NormalWidget";
	_isChenile = false;

	fillButtonList();
	initConnection();

	connect(this, &CCAbstractWidget::sigSendClickButton, this, &NormalWidget::slotClickButtonNeedle);
	connect(this, &CCAbstractWidget::sigSendClickButton, this, &NormalWidget::slotClickButtonARM);
}

NormalWidget::~NormalWidget()
{

}

void NormalWidget::fillButtonList()
{
	const char* prName = "SetColor";

	ui.pB_1_->setProperty(prName,  true);
	ui.pB_2_->setProperty(prName,  true);
	ui.pB_3_->setProperty(prName,  true);
	ui.pB_4_->setProperty(prName,  true);
	ui.pB_5_->setProperty(prName,  true);
	ui.pB_6_->setProperty(prName,  true);
	ui.pB_7_->setProperty(prName,  true);
	ui.pB_8_->setProperty(prName,  true);
	ui.pB_9_->setProperty(prName,  true);
	ui.pB_10_->setProperty(prName, true);
	ui.pB_11_->setProperty(prName, true);
	ui.pB_12_->setProperty(prName, true);
	ui.pB_13_->setProperty(prName, true);
	ui.pB_14_->setProperty(prName, true);
	ui.pB_15_->setProperty(prName, true);

	ui.pB_1->setProperty(prName,  false);
	ui.pB_2->setProperty(prName,  false);
	ui.pB_3->setProperty(prName,  false);
	ui.pB_4->setProperty(prName,  false);
	ui.pB_5->setProperty(prName,  false);
	ui.pB_6->setProperty(prName,  false);
	ui.pB_7->setProperty(prName,  false);
	ui.pB_8->setProperty(prName,  false);
	ui.pB_9->setProperty(prName,  false);
	ui.pB_10->setProperty(prName, false);
	ui.pB_11->setProperty(prName, false);
	ui.pB_12->setProperty(prName, false);
	ui.pB_13->setProperty(prName, false);
	ui.pB_14->setProperty(prName, false);
	ui.pB_15->setProperty(prName, false);

	/*QPixmap fPixmap = QPixmap("Resources/icon_center_f.png");
	QPixmap rPixmap = QPixmap("Resources/icon_center_r.png");
	QPixmap aPixmap = QPixmap("Resources/icon_center_a.png");

	ui.pBLeftEvenF->setProperty(prName, convert(CCTableItem(15, fPixmap,"EV")));
	ui.pBLeftEvenR->setProperty(prName, convert(CCTableItem(15, rPixmap,"EV")));
	ui.pBLeftEvenA->setProperty(prName, convert(CCTableItem(15, aPixmap,"EV")));

	ui.pBLeftAllF->setProperty(prName, convert(CCTableItem(15, fPixmap,"AL")));
	ui.pBLeftAllR->setProperty(prName, convert(CCTableItem(15, rPixmap,"AL")));
	ui.pBLeftAllA->setProperty(prName, convert(CCTableItem(15, aPixmap,"AL")));

	ui.pBLeftOddF->setProperty(prName, convert(CCTableItem(15, fPixmap,"OD")));
	ui.pBLeftOddR->setProperty(prName, convert(CCTableItem(15, rPixmap,"OD")));
	ui.pBLeftOddA->setProperty(prName, convert(CCTableItem(15, aPixmap,"OD")));

	ui.pBRightEvenF->setProperty(prName, convert(CCTableItem(15, fPixmap,"EV")));
	ui.pBRightEvenR->setProperty(prName, convert(CCTableItem(15, rPixmap,"EV")));
	ui.pBRightEvenA->setProperty(prName, convert(CCTableItem(15, aPixmap,"EV")));

	ui.pBRightAllF->setProperty(prName, convert(CCTableItem(15, fPixmap, "AL")));
	ui.pBRightAllR->setProperty(prName, convert(CCTableItem(15, rPixmap, "AL")));
	ui.pBRightAllA->setProperty(prName, convert(CCTableItem(15, aPixmap, "AL")));

	ui.pBRightOddF->setProperty(prName, convert(CCTableItem(15, fPixmap, "OD")));
	ui.pBRightOddR->setProperty(prName, convert(CCTableItem(15, rPixmap, "OD")));
	ui.pBRightOddA->setProperty(prName, convert(CCTableItem(15, aPixmap, "OD")));*/

	_btnList.append(ui.pB_1_);
	_btnList.append(ui.pB_2_);
	_btnList.append(ui.pB_3_);
	_btnList.append(ui.pB_4_);
	_btnList.append(ui.pB_5_);
	_btnList.append(ui.pB_6_);
	_btnList.append(ui.pB_7_);
	_btnList.append(ui.pB_8_);
	_btnList.append(ui.pB_9_);
	_btnList.append(ui.pB_10_);
	_btnList.append(ui.pB_11_);
	_btnList.append(ui.pB_12_);
	_btnList.append(ui.pB_13_);
	_btnList.append(ui.pB_14_);
	_btnList.append(ui.pB_15_);

	_btnList.append(ui.pB_1);
	_btnList.append(ui.pB_2);
	_btnList.append(ui.pB_3);
	_btnList.append(ui.pB_4);
	_btnList.append(ui.pB_5);
	_btnList.append(ui.pB_6);
	_btnList.append(ui.pB_7);
	_btnList.append(ui.pB_8);
	_btnList.append(ui.pB_9);
	_btnList.append(ui.pB_10);
	_btnList.append(ui.pB_11);
	_btnList.append(ui.pB_12);
	_btnList.append(ui.pB_13);
	_btnList.append(ui.pB_14);
	_btnList.append(ui.pB_15);
	 
	_btnList.append(ui.pBLeftEvenF);
	_btnList.append(ui.pBLeftEvenR);
	_btnList.append(ui.pBLeftEvenA);

	_btnList.append(ui.pBLeftAllF);
	_btnList.append(ui.pBLeftAllR);
	_btnList.append(ui.pBLeftAllA);

	_btnList.append(ui.pBLeftOddF);
	_btnList.append(ui.pBLeftOddR);
	_btnList.append(ui.pBLeftOddA);

	_btnList.append(ui.pBRightEvenF);
	_btnList.append(ui.pBRightEvenR);
	_btnList.append(ui.pBRightEvenA);

	_btnList.append(ui.pBRightAllF);
	_btnList.append(ui.pBRightAllR);
	_btnList.append(ui.pBRightAllA);

	_btnList.append(ui.pBRightOddF);
	_btnList.append(ui.pBRightOddR);
	_btnList.append(ui.pBRightOddA);
}

void NormalWidget::slotClickButtonNeedle(QPushButton* btn)
{
	bool entered = false;

	NeedleSet inputData;
	if (ui.pB_1 == btn)
	{
		entered = true;
		inputData.Needle = 1;
		inputData.Group = 0;
	}
	else if (ui.pB_2 == btn)
	{
		entered = true;
		inputData.Needle = 2;
		inputData.Group = 0;
	}
	else if (ui.pB_3 == btn)
	{
		entered = true;
		inputData.Needle = 3;
		inputData.Group = 0;
	}
	else if (ui.pB_4 == btn)
	{
		entered = true;
		inputData.Needle = 4;
		inputData.Group = 0;
	}
	else if (ui.pB_5 == btn)
	{
		entered = true;
		inputData.Needle = 5;
		inputData.Group = 0;
	}
	else if (ui.pB_6 == btn)
	{
		entered = true;
		inputData.Needle = 6;
		inputData.Group = 0;
	}
	else if (ui.pB_7 == btn)
	{
		entered = true;
		inputData.Needle = 7;
		inputData.Group = 0;
	}
	else if (ui.pB_8 == btn)
	{
		entered = true;
		inputData.Needle = 8;
		inputData.Group = 0;
	}
	else if (ui.pB_9 == btn)
	{
		entered = true;
		inputData.Needle = 9;
		inputData.Group = 0;
	}
	else if (ui.pB_10 == btn)
	{
		entered = true;
		inputData.Needle = 10;
		inputData.Group = 0;
	}
	else if (ui.pB_11 == btn)
	{
		entered = true;
		inputData.Needle = 11;
		inputData.Group = 0;
	}
	else if (ui.pB_12 == btn)
	{
		entered = true;
		inputData.Needle = 12;
		inputData.Group = 0;
	}
	else if (ui.pB_13 == btn)
	{
		entered = true;
		inputData.Needle = 13;
		inputData.Group = 0;
	}
	else if (ui.pB_14 == btn)
	{
		entered = true;
		inputData.Needle = 14;
		inputData.Group = 0;
	}
	else if (ui.pB_15 == btn)
	{
		entered = true;
		inputData.Needle = 15;
		inputData.Group = 0;
	}

	if (entered)
	{
		modifyNeedleSetWithOffsetAndStop(inputData);
		setNeedleSetToModel(inputData);
	}
}

void NormalWidget::slotClickButtonARM(QPushButton* btn)
{
	bool entered = false;

	quint16 NT_SequinFront = 0x2000;
	quint16 NT_SequinRear = 0x1000;
	int MaxNeedleNum = 15;

	NeedleSet inputData;
	#pragma region Left
		#pragma region Even
		if (ui.pBLeftEvenF == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinFront | (MaxNeedleNum));;
			inputData.Group = 2;
		}
		else if (ui.pBLeftEvenR == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinRear | (MaxNeedleNum));
			inputData.Group = 2;
		}
		else if (ui.pBLeftEvenA == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinFront | NT_SequinRear | (MaxNeedleNum));
			inputData.Group = 2;
		}
		#pragma endregion
		#pragma region All
		else if (ui.pBLeftAllF == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinFront | (MaxNeedleNum));
			inputData.Group = 0;
		}
		else if (ui.pBLeftAllR == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinRear | (MaxNeedleNum));
			inputData.Group = 0;
		}
		else if (ui.pBLeftAllA == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinFront | NT_SequinRear | (MaxNeedleNum));
			inputData.Group = 0;
		}
		#pragma endregion
		#pragma region Odd
		else if (ui.pBLeftOddF == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinFront | (MaxNeedleNum));
			inputData.Group = 1;
		}
		else if (ui.pBLeftOddR == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinRear | (MaxNeedleNum));
			inputData.Group = 1;
		}
		else if (ui.pBLeftOddA == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinFront | NT_SequinRear | (MaxNeedleNum));
			inputData.Group = 1;
		}
		#pragma endregion
	#pragma endregion
	
	#pragma region Right
		#pragma region Even
		else if (ui.pBRightEvenF == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinFront | 1);;
			inputData.Group = 2;
		}
		else if (ui.pBRightEvenR == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinRear | 1);
			inputData.Group = 2;
		}
		else if (ui.pBRightEvenA == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinFront | NT_SequinRear | 1);
			inputData.Group = 2;
		}
		#pragma endregion
		#pragma region All
		else if (ui.pBRightAllF == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinFront | 1);
			inputData.Group = 0;
		}
		else if (ui.pBRightAllR == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinRear | 1);
			inputData.Group = 0;
		}
		else if (ui.pBRightAllA == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinFront | NT_SequinRear | 1);
			inputData.Group = 0;
		}
		#pragma endregion
		#pragma region Odd
		else if (ui.pBRightOddF == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinFront | 1);
			inputData.Group = 1;
		}
		else if (ui.pBRightOddR == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinRear | 1);
			inputData.Group = 1;
		}
		else if (ui.pBRightOddA == btn)
		{
			entered = true;
			inputData.Needle = (quint16)(NT_SequinFront | NT_SequinRear | 1);
			inputData.Group = 1;
		}
		#pragma endregion
	#pragma endregion

	if (entered)
		setNeedleSetToModel(inputData);
}