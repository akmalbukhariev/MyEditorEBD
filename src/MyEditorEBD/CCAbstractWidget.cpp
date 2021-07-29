#include "CCAbstractWidget.h"

#include <QDebug>
#include <QColorDialog>

/*Needle type (16bit)

	15	   | 14	  | 13	         | 12	        | 11	        | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0
	Offset | Stop | Sequin Front | Sequin Rear  | Taping Bobbin | Type of needle | Number
	
	iv.	Type of needle : Operation by work type
	0	: Normal
	1	: Chenille – Loop
	2	: Chenille – Chain
	3	: Chenille - Reserved
	4	: Taping – Normal
	5	: Taping – Tape
	6	: Taping – Coil
	7	: Taping – Frill
	8	~  13 : Taping – Zigzag1 ~ Zigzag 6
	14	~  15 : Taping – Reserved
*/

CCAbstractWidget::CCAbstractWidget(QWidget* parent)
	: QWidget(parent)
{
	//_className = "";
}

CCAbstractWidget::~CCAbstractWidget()
{
	//qDebug() << _className;
}

void CCAbstractWidget::initConnection()
{
	for each(QPushButton* btn in _btnList)
	{
		connect(btn, &QPushButton::clicked, this, &CCAbstractWidget::slotClickButton);
	}
}

void CCAbstractWidget::setEbdInfo(EbdFileInfo* ebdInfo)
{
	_ebdInfo = ebdInfo;
}

void CCAbstractWidget::updateColorButtons()
{
	CCTableModel* ccModel = _tableView->ccTableModel();

	for each(QPushButton* btn in _btnList)
	{
		int idx = getButtonIndex(btn);

		if (idx >= 0)
			setColorButton(btn, ccModel->DesignColor[idx]);
	}
}

void CCAbstractWidget::slotClickButton()
{
	for each (QPushButton* btn in _btnList)
	{
		if (sender() == btn)
		{
			bool use = btn->property("SetColor").toBool();
			if (use)
			{
				QColorDialog colorDialog;
				if (!colorDialog.exec()) return;

				QColor color = colorDialog.selectedColor();
				setColorButton(btn, color);

				int idx = getButtonIndex(btn);
				if (idx >= 0)
				{
					_tableView->ccTableModel()->DesignColor[idx] = color;
					emit sigSendClickColorButton(_isChenile);
				}
			}
			else
			{
				emit sigSendClickButton(btn);
			}
			break;
		}
	}
}

void CCAbstractWidget::setColorButton(QPushButton* btn, const QColor& color)
{
	int r = 0;
	int g = 0;
	int b = 0;
	color.getRgb(&r, &g, &b);

	QString strColor = "background-color: " + color.name(QColor::HexArgb) + "; \n color: ";

	if (r >= 200 && r <= 255 && g >= 200 && g <= 255 && b >= 200 && b <= 255)
	{
		strColor.append("black;");
	}
	else if (r == g && r == b && g == b)
	{
		strColor.append("white;");
	}

	btn->setStyleSheet(strColor);
}

void CCAbstractWidget::setNeedleSetToModel(const NeedleSet& nInfo)
{
	int row = _tableView->currentIndex().row();
	CCTableModel * ccModel = _tableView->ccTableModel();
	
	ccModel->getData()[row].Needle = nInfo.Needle;
	ccModel->getData()[row].Option = nInfo.Option;
	ccModel->getData()[row].Group = nInfo.Group;

	if (_tableView->ccTableModel()->rowCount() > row + 1)
	{
		row++;
	}

	ccModel->reset();
	_tableView->clearSelection();
	_tableView->setCurrentIndex(row);
	_tableView->selectRow(row);
}

void CCAbstractWidget::modifyNeedleSetWithOffsetAndStop(NeedleSet& nInfo)
{
	quint16 NT_Offset = 0x8000;
	quint16 NT_Stop = 0x4000;

	int curIndex = _tableView->currentIndex().row();
	CCTableModel* ccModel = _tableView->ccTableModel();
	nInfo.Needle = (quint16)((ccModel->getData()[curIndex].Needle & (NT_Offset | NT_Stop)) | nInfo.Needle);
}

int CCAbstractWidget::getButtonIndex(QPushButton* btn)
{
	QString strName = btn->objectName();

	int idx = -1;

	if (strName == "pB_1_" || strName == "pB_L1_" || strName == "pB_C1_")
	{
		idx = 0;
	}
	else if (strName == "pB_2_" || strName == "pB_L2_" || strName == "pB_C2_")
	{
		idx = 1;
	}
	else if (strName == "pB_3_" || strName == "pB_L3_" || strName == "pB_C3_")
	{
		idx = 2;
	}
	else if (strName == "pB_4_" || strName == "pB_L4_" || strName == "pB_C4_")
	{
		idx = 3;
	}
	else if (strName == "pB_5_" || strName == "pB_L5_" || strName == "pB_C5_")
	{
		idx = 4;
	}
	else if (strName == "pB_6_" || strName == "pB_L6_" || strName == "pB_C6_")
	{
		idx = 5;
	}
	else if (strName == "pB_7_")
	{
		idx = 6;
	}
	else if (strName == "pB_8_")
	{
		idx = 7;
	}
	else if (strName == "pB_9_")
	{
		idx = 8;
	}
	else if (strName == "pB_10_")
	{
		idx = 9;
	}
	else if (strName == "pB_11_")
	{
		idx = 10;
	}
	else if (strName == "pB_12_")
	{
		idx = 11;
	}
	else if (strName == "pB_13_")
	{
		idx = 12;
	}
	else if (strName == "pB_14_")
	{
		idx = 13;
	}
	else if (strName == "pB_15_")
	{
		idx = 14;
	}

	return idx;
}