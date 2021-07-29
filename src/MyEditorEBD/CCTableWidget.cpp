#include "CCTableWidget.h"

#include <QHeaderView>
#include <QMouseEvent>

CCTableWidget::CCTableWidget(QWidget* parent)
	:QTableWidget(parent)
{
	initUI();
	initMenu();
	initConnection();
	_ccDelegate = new CCTableItemDelegate(this);
	setItemDelegate(_ccDelegate);

	//setModel
}

CCTableWidget::~CCTableWidget()
{

}

void CCTableWidget::initUI()
{
	setRowCount(0);
	setColumnCount(4);
	QStringList strHeader;
	strHeader << "N" << "T" << "H" << "G";

	setColumnWidth(0, 50);
	setColumnWidth(1, 47);
	setColumnWidth(2, 50);
	setColumnWidth(3, 58);
	
	//resizeRowsToContents();

	//verticalHeader()->setDefaultSectionSize(25);
	setHorizontalHeaderLabels(strHeader);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setSelectionMode(QAbstractItemView::SingleSelection);
	//horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void CCTableWidget::initMenu()
{
	_actionOffset = new QAction("Add offset or Stop");
	_menu.addAction(_actionOffset);
}

void CCTableWidget::initConnection()
{
	connect(_actionOffset, &QAction::triggered, this, &CCTableWidget::slotClickMenu);
}

void CCTableWidget::paintEvent(QPaintEvent* event)
{
	QTableView::paintEvent(event);
	QPainter painter(viewport());
	QPen pen;
	QFont fontText;
	fontText.setPointSize(15);
	pen.setColor(QColor(128, 128, 255, 128));
	pen.setWidth(6);
	painter.setFont(fontText);
	painter.setPen(pen);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QPoint center = viewport()->rect().center();

	QString strMessage;
	if (model()->rowCount() == 0)
		strMessage = "No Color Info";

	painter.drawText(viewport()->rect(), Qt::AlignCenter, strMessage);
}

void CCTableWidget::mouseReleaseEvent(QMouseEvent* event)
{
	QModelIndex index = indexAt(event->pos());
	_row = index.row();

	if (event->button() == Qt::RightButton)
	{
		_menu.popup(mapToGlobal(event->pos()));
		_menu.show();
	}
	 
	QTableWidget::mouseReleaseEvent(event);
}

void CCTableWidget::setEbdInfo(EbdFileInfo* ebdInfo)
{
	for (int i = 1; i <= ebdInfo->ebdHeader.ColorChangeNum; i++)
	{
		if (i >= ebdInfo->ebdHeader.CCTableData.count())
			break;

		insertRow(i - 1);

		QTableWidgetItem* item0 = new QTableWidgetItem();
		item0->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		item0->setTextAlignment(Qt::AlignCenter);

		QTableWidgetItem* item1 = new QTableWidgetItem();
		item1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		item1->setTextAlignment(Qt::AlignCenter);

		QTableWidgetItem* item2 = new QTableWidgetItem();
		item2->setTextAlignment(Qt::AlignCenter);

		QTableWidgetItem* item3 = new QTableWidgetItem();
		item3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		item3->setTextAlignment(Qt::AlignCenter);
		 
		setItem(i - 1, 0, item0);
		setItem(i - 1, 1, item1);
		setItem(i - 1, 2, item2);
		setItem(i - 1, 3, item3);

		selectRow(i - 1);
		setRowHeight(model()->rowCount() - 1, 40);
		
		CCTableItem ccItem = convertToCCItem(ebdInfo, i);
		slotInsertRow(ccItem);
	}
}

CCTableItem CCTableWidget::convertToCCItem(EbdFileInfo* ebdInfo, int i)
{
	CCTableItem ccItem;

	quint16 value = ebdInfo->ebdHeader.CCTableData[i].Needle;

	int temp = value & 0x3000; //0x6000;
	int TValue = (char)(temp >> 11);

	int mtemp = value & 0x780; //0xf00;
	int Mode = (char)(mtemp >> 7);

	int ttemp = value & 0x800; //0x1000;
	int bobbin = (char)(ttemp >> 11);

	ccItem.Needle = convertToNeedle(ebdInfo, i);
	ccItem.Group = convertToGroup(ebdInfo, i);
	ccItem.Height = ebdInfo->ebdHeader.CCTableData[i].Height;

	if (Mode == 0)
	{
		switch (TValue)
		{
			case 2: ccItem.Type = QPixmap("Resources/icon_center_r.png"); break; //Rear
			case 4: ccItem.Type = QPixmap("Resources/icon_center_f.png"); break; //Front
			case 6: ccItem.Type = QPixmap("Resources/icon_center_a.png"); break; //All
		}
	}
	else
	{
		switch (Mode)
		{
			//Chenille
			case 1: ccItem.Type = QPixmap("Resources/L.png"); break;
			case 2: ccItem.Type = QPixmap("Resources/C.png"); break;

			//Taping
			case 4: ccItem.Type = QPixmap("Resources/icon_list_tn.png");														 break; //Normal
			case 5: ccItem.Type = (bobbin == 0) ? QPixmap("Resources/icon_list_tf.png") : QPixmap("Resources/icon_list_tr.png"); break; //Tape
			case 6: ccItem.Type = (bobbin == 0) ? QPixmap("Resources/icon_list_cf.png") : QPixmap("Resources/icon_list_cr.png"); break; //Coil
			case 7: ccItem.Type = (bobbin == 0) ? QPixmap("Resources/icon_list_ff.png") : QPixmap("Resources/icon_list_fr.png"); break; //Frill 

			//Zigzag
			case 8:  ccItem.Type = QPixmap("Resources/icon_z1.png"); break;
			case 9:  ccItem.Type = QPixmap("Resources/icon_z2.png"); break;
			case 10: ccItem.Type = QPixmap("Resources/icon_z3.png"); break;
			case 11: ccItem.Type = QPixmap("Resources/icon_z4.png"); break;
			case 12: ccItem.Type = QPixmap("Resources/icon_z5.png"); break;
			case 13: ccItem.Type = QPixmap("Resources/icon_z6.png"); break;
			default: break;
		}
	}

	return ccItem;
}

int CCTableWidget::convertToNeedle(EbdFileInfo* ebdInfo, int i)
{
	int needle = 1;
	int temp = ebdInfo->ebdHeader.CCTableData[i].Needle & 0x7f;//0x3f
	needle = (char)temp;

	return needle;
}

//Option CCTableWidget::convertToType(EbdFileInfo* ebdInfo, int i)
//{
//	Option option = None;
//
//	quint16 value = ebdInfo->ebdHeader.CCTableData[i].Needle;
//
//	int temp = value & 0x3000; //0x6000;
//	int TValue = (char)(temp >> 11);
//
//	int mtemp = value & 0x780; //0xf00;
//	int Mode = (char)(mtemp >> 7);
//
//	int ttemp = value & 0x800; //0x1000;
//	int bobbin = (char)(ttemp >> 11);
//
//	if (Mode == 0)
//	{
//		int needleNumber = convertToNeedle(ebdInfo, i);
//		QString strGroup = convertToGroup(ebdInfo, i);
//
//		switch (TValue)
//		{
//			case 2: //Rear
//				if (needleNumber == 1)
//				{
//					if (strGroup == "AL") option = RightAllR;
//					if (strGroup == "OD") option = RightOddR;
//					if (strGroup == "EV") option = RightEvenR;
//				}
//				else
//				{
//					if (strGroup == "AL") option = LeftAllR;
//					if (strGroup == "OD") option = LeftOddR;
//					if (strGroup == "EV") option = LeftEvenR;
//				}
//				break; 
//			case 4: //Front
//				if (needleNumber == 1)
//				{
//					if (strGroup == "AL") option = RightAllF;
//					if (strGroup == "OD") option = RightOddF;
//					if (strGroup == "EV") option = RightEvenF;
//				}
//				else
//				{
//					if (strGroup == "AL") option = LeftAllF;
//					if (strGroup == "OD") option = LeftOddF;
//					if (strGroup == "EV") option = LeftEvenF;
//				}
//				break; 
//			case 6: //All
//				if (needleNumber == 1)
//				{
//					if (strGroup == "AL") option = RightAllA;
//					if (strGroup == "OD") option = RightOddA;
//					if (strGroup == "EV") option = RightEvenA;
//				}
//				else
//				{
//					if (strGroup == "AL") option = LeftAllA;
//					if (strGroup == "OD") option = LeftOddA;
//					if (strGroup == "EV") option = LeftEvenA;
//				}
//				break; 
//		}
//	}
//	else
//	{
//		switch (Mode)
//		{
//			//Chenille
//			case 1: option = L; break;
//			case 2: option = C; break;
//			case 3: break;
//
//			//Taping
//			case 4: option = Normal; break;
//			case 5: option = (bobbin == 0) ? TapeF : TapeR;   break;
//			case 6: option = (bobbin == 0) ? CoilF : CoilR;   break;
//			case 7: option = (bobbin == 0) ? FrillF : FrillR; break;
//			case 8: option = Z1;  break;
//			case 9: option = Z2;  break;
//			case 10: option = Z3; break;
//			case 11: option = Z4; break;
//			case 12: option = Z5; break;
//			case 13: option = Z6; break;
//		}
//	}
//
//	return option;
//}

QString CCTableWidget::convertToGroup(EbdFileInfo* ebdInfo, int i)
{
	QString return_STR = "";

	switch (ebdInfo->ebdHeader.CCTableData[i].Group)
	{
		case 0:
			return_STR = "AL";
			break;

		case 1:
			return_STR = "OD";
			break;

		case 2:
			return_STR = "EV";
			break;

		default:
			break;
	}

	return return_STR;
}

void CCTableWidget::slotClickMenu()
{
	//QString ss = getSelectedItem(2)->text();
	//int y = 0;
}

void CCTableWidget::slotInsertRow(const CCTableItem& ccItem)
{
	QTableWidgetItem* tItem0 = getSelectedItem(0);
	QTableWidgetItem* tItem1 = getSelectedItem(1);
	QTableWidgetItem* tItem3 = getSelectedItem(3);

	tItem0->setText(QString::number(ccItem.Needle));
	if (!ccItem.Type.isNull())
		tItem1->setData(Qt::DecorationRole, ccItem.Type.scaled(QSize(35, 35)));

	tItem3->setText(ccItem.Group);

	if (model()->rowCount() > currentRow())
		selectRow(currentRow() + 1);
}

CCTableItem CCTableWidget::getCCItem(int row)
{
	CCTableItem ccItem;

	return ccItem;
}

void CCTableWidget::saveEbdFile()
{
	for (int i = 0; i < model()->rowCount(); i++) 
	{
		quint16 Needle;
		quint16 Option;
		quint16 Height;
		quint16 Group;

		Needle = item(i, 0)->text().toUShort();
	}
}

void CCTableWidget::removeRow()
{
	model()->removeRow(_row);
}

QTableWidgetItem* CCTableWidget::getSelectedItem(int col)
{
	QTableWidgetItem* temp = item(currentRow(), col);
	if (col != 1) return temp;

	if (temp != nullptr)
	{
		delete temp;
		temp = nullptr;

		temp = new QTableWidgetItem();
		temp->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		setItem(currentRow(), col, temp);
	}
	
	return temp;
}

void CCTableWidget::clean()
{
	while (model()->rowCount() > 0)
	{
		model()->removeRow(0);
	}
}