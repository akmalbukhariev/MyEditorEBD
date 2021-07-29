
#include "Control.h"
#include "CCTableDialog.h"

#include <QDebug>
#include <QMessageBox>

CCTableDialog::CCTableDialog(EbdFileInfo* ebdInfo, QWidget* parent)
	: _ebdInfo(ebdInfo), QDialog(parent)
{
	ui.setupUi(this);
	 
	_ccModel = Q_NULLPTR;
	_ccModel = new CCTableModel(this);
	_ccModel->setEbdFileInfo(_ebdInfo);
	ui.tWCCTableView->setModel(_ccModel);

	//initUI();
	initConnection();
	initTable();
}

CCTableDialog::~CCTableDialog()
{
	if (_ccModel != Q_NULLPTR)
	{
		delete _ccModel;
		_ccModel = Q_NULLPTR;
	}
}

void CCTableDialog::initUI()
{
	ui.tabWidgets->setCurrentIndex(0);

	ui.wDNormal->setTableView(ui.tWCCTableView);
	ui.wDChenile->setTableView(ui.tWCCTableView);
	ui.wDTape->setTableView(ui.tWCCTableView);

	ui.wDNormal->setEbdInfo(_ebdInfo);
	ui.wDChenile->setEbdInfo(_ebdInfo);
	ui.wDTape->setEbdInfo(_ebdInfo);

	ui.wDNormal->updateColorButtons();
	ui.wDChenile->updateColorButtons();
	//ui.wDTape->updateColorButtons();
}

void CCTableDialog::initCCTableVIew()
{
	_ccModel->getData().clear();
	for (int i = 1; i <= _ebdInfo->ebdHeader.ColorChangeNum; i++)
	{
		NeedleSet item;
		//item.useColor = false;
		item.Needle = 0;
		item.Group = 0;
		item.Height = 0;
		item.Option = 0;

		if (i == 1)
			item.Needle = 1;

		_ccModel->setData(item);
	}
}

void CCTableDialog::initTable()
{ 
	bool first = true;
	int index = 0;

	initCCTableVIew();

	for each (NeedleSet needle in _ebdInfo->ebdHeader.CCTableData)
	{
		if (needle.Needle == 0 && first)
		{
			first = false;
			continue;
		}
		index++;

		if (_ccModel->rowCount() >= index)
			_ccModel->getData()[index - 1] = needle;
		else
			_ccModel->setData(needle);
	}

	if (_ebdInfo->ebdHeader.MCColorPaletteDataSize == 0)
	{
		initUI();
		slotInitButton();
	}
	else
	{
		for (int i = 0; i < _ebdInfo->ebdHeader.MCColorPaletteDataSize / 4; i++)
		{
			quint32 item = _ebdInfo->ebdHeader.MCColorPaletteData[i];

			int color = (int)item & 0x00ffffff;
			int itemNeedleNum = (int)item & 0x7f000000;

			int r = (quint8)(color >> 16);
			int g = (quint8)(color >> 8);
			int b = (quint8)(color >> 0);

			QColor itemColor = QColor::fromRgb(r, g, b, 0xFF);
			int num = (char)(itemNeedleNum >> 24);

			if (num == 0 || num > _ccModel->MaxNeedleNum)
				continue;

			_ccModel->DesignColor[num - 1] = itemColor;
		}
	}

	_ccModel->reset();

	ui.tWCCTableView->initView();
	initUI();
}

void CCTableDialog::initConnection()
{
	connect(ui.pBSave, &QPushButton::clicked, this, &CCTableDialog::slotSaveButton);
	connect(ui.pBInit, &QPushButton::clicked, this, &CCTableDialog::slotInitButton);
	connect(ui.pBAdd, &QPushButton::clicked, this, &CCTableDialog::slotAddCC);
	connect(ui.pBRemove, &QPushButton::clicked, this, &CCTableDialog::slotRemoveCC);

	connect(ui.wDNormal, &NormalWidget::sigSendClickColorButton, this, &CCTableDialog::slotClickColorButton);
	connect(ui.wDChenile, &ChenileWidget::sigSendClickColorButton, this, &CCTableDialog::slotClickColorButton);
}

void CCTableDialog::initNeedleColor()
{
	qint32* needleColor = NeedleColor().Color;

	for (int i = 0; i < _ccModel->MaxNeedleNum + 1; i++)
	{
		_ccModel->DesignColor[i] = QColor::fromRgb((quint8)(needleColor[i + 1] >> 16),
												   (quint8)(needleColor[i + 1] >> 8),
												   (quint8)(needleColor[i + 1] >> 0), 0xFF);
	}

	ui.wDNormal->setEbdInfo(_ebdInfo);
	ui.wDChenile->setEbdInfo(_ebdInfo);
	ui.wDTape->setEbdInfo(_ebdInfo);

	ui.wDNormal->updateColorButtons();
	ui.wDChenile->updateColorButtons();
	ui.wDTape->updateColorButtons();
}

void CCTableDialog::slotSaveButton()
{  
	#pragma region Init

	_ebdInfo->ebdHeader.CCTableData.clear();
	if (_ebdInfo->ebdHeader.MCColorPaletteData != Q_NULLPTR)
	{
		delete[] _ebdInfo->ebdHeader.MCColorPaletteData;
		_ebdInfo->ebdHeader.MCColorPaletteData = Q_NULLPTR;
	}

	int needleCount = _ebdInfo->ebdHeader.ColorChangeNum;

	if (_ebdInfo->ebdHeader.CCTableData.count() == 0 || needleCount >= _ebdInfo->ebdHeader.CCTableData.count())
	{
		for (int i = 0; i < needleCount + 1; i++)
		{
			_ebdInfo->ebdHeader.CCTableData.append(NeedleSet());
		}

		_ebdInfo->ebdHeader.MCColorPaletteData = new quint32[_ccModel->MaxNeedleNum + 1];
		_ebdInfo->ebdHeader.CCTableSize = (uint)((needleCount + 1) * 8);
		_ebdInfo->ebdHeader.MCColorPaletteDataSize = (uint)((_ccModel->MaxNeedleNum + 1) * 4);
	}

	#pragma endregion

	#pragma region Save Needle

	int i = 1;

	QList<NeedleSet> arrneedle;
	for each (NeedleSet needle in _ccModel->getData())
	{
		if (i != 0 && needle.Needle != 0)
		{
			_ebdInfo->changed = true;
		}

		if (needle.Needle != 0)
		{
			_ebdInfo->ebdHeader.CCTableData[i].Needle = needle.Needle;
			_ebdInfo->ebdHeader.CCTableData[i].Group = needle.Group;
			_ebdInfo->ebdHeader.CCTableData[i].Height = needle.Height;
			_ebdInfo->ebdHeader.CCTableData[i].Option = needle.Option;
		}
		else
		{
			arrneedle = _ebdInfo->ebdHeader.CCTableData;

			for (int cnt = 0; cnt < i; cnt++)
			{
				_ebdInfo->ebdHeader.CCTableData[cnt] = arrneedle[cnt];
			}
			_ebdInfo->ebdHeader.CCTableSize = (uint)(_ebdInfo->ebdHeader.CCTableData.count() * 8);
			break;
		}

		i++;
	}

	#pragma endregion

	#pragma region Palette color

	for (int count = 0; count <= _ccModel->MaxNeedleNum; count++)
	{
		if (count == 0)
		{
			_ebdInfo->ebdHeader.MCColorPaletteData[count] = 0;
		}
		else
		{
			quint32 color = (quint32)((count << 24) + colorToInt(_ccModel->DesignColor[count - 1], false));
			
			if (color != _ebdInfo->ebdHeader.MCColorPaletteData[count])
				_ebdInfo->changed = true;

			_ebdInfo->ebdHeader.MCColorPaletteData[count] = color;
		}
	}

	_ebdInfo->ebdHeader.MCColorPaletteDataSize = (uint)((_ccModel->MaxNeedleNum + 1) * 4);

	#pragma endregion

	//QMessageBox::information(this, "CC Info", "CC table info has saved.", QMessageBox::Ok);
	Control::instance()->showMessageBox(this, "CC Info", "CC table info has saved.");
	this->close();
}

void CCTableDialog::slotInitButton()
{
	initNeedleColor();
	initCCTableVIew();
	_ccModel->reset();
	ui.tWCCTableView->selectRow(0);

	//QMessageBox::information(this, "Init", "Initialized CC Dialog", QMessageBox::Ok);
	//Control::instance()->showMessageBox(this, "Init", "Initialized CC Dialog");
}

void CCTableDialog::slotAddCC()
{
	bool bNeedleZero = false;
	for (int i = 0; i < _ccModel->rowCount(); i++)
	{
		if (_ccModel->getData()[i].Needle == 0)
		{
			bNeedleZero = true;
			break;
		}
	}

	if (bNeedleZero == false)
		return;

	int curIndex = ui.tWCCTableView->currentIndex().row();
	int index = curIndex == 0 ? 0 : curIndex - 1;

	QList<NeedleSet> TempDesignList;
	for (int i = 0; i < _ccModel->rowCount(); i++)
	{
		if (i < curIndex)
			TempDesignList.append(_ccModel->getData()[i]);
		else if (i == curIndex)
		{
			NeedleSet item;
			item.Needle = _ccModel->getData()[index].Needle;
			item.Group =  _ccModel->getData()[index].Group;
			item.Height = _ccModel->getData()[index].Height;
			item.Option = _ccModel->getData()[index].Option;

			if (i == 0)
			{
				TempDesignList.append(_ccModel->getData()[i]);
				TempDesignList.append(item);
			}
			else if (curIndex == _ccModel->rowCount() - 1)
			{
				TempDesignList.append(item);
			}
			else
			{
				TempDesignList.append(item);

				NeedleSet item_1;;
				item_1.Needle = _ccModel->getData()[i].Needle;
				item_1.Group =  _ccModel->getData()[i].Group;
				item_1.Height = _ccModel->getData()[i].Height;
				item_1.Option = _ccModel->getData()[i].Option;

				TempDesignList.append(item_1);
			}
		}
		else 
		{
			if (i == _ccModel->rowCount() - 1)
				break;

			NeedleSet item;
			item.Needle = _ccModel->getData()[i].Needle;
			item.Group =  _ccModel->getData()[i].Group;
			item.Height = _ccModel->getData()[i].Height;
			item.Option = _ccModel->getData()[i].Option;

			TempDesignList.append(item);
		}
	}
	 
	modifyModelData(TempDesignList);

	if (curIndex < _ccModel->rowCount())
		curIndex++;

	ui.tWCCTableView->clearSelection();
	ui.tWCCTableView->selectRow(curIndex);
}

void CCTableDialog::slotRemoveCC()
{
	int nNeedleNotZero = 0;
	for (int i = 0; i < _ccModel->rowCount(); i++)
	{
		if (_ccModel->getData()[i].Needle != 0)
		{
			nNeedleNotZero++;
		}
	}

	if (nNeedleNotZero < 2)
		return;

	int curIndex = ui.tWCCTableView->currentIndex().row();

	QList <NeedleSet> TempDesignList;
	for (int i = 0; i < _ccModel->rowCount(); i++)
	{
		if (i < curIndex)
		{
			TempDesignList.append(_ccModel->getData()[i]);
		}
		else if (i == curIndex)
		{
			//Not add curIndexItem
		}
		else
		{
			NeedleSet item;
			item.Needle = _ccModel->getData()[i].Needle;
			item.Group =  _ccModel->getData()[i].Group;
			item.Height = _ccModel->getData()[i].Height;
			item.Option = _ccModel->getData()[i].Option;

			TempDesignList.append(item);
		}

		if (i == _ccModel->rowCount() - 1)
		{
			NeedleSet item;
			item.Needle = 0;
			item.Group = 0;
			item.Height = 0;
			item.Option = 0;

			TempDesignList.append(item);
		}
	}

	modifyModelData(TempDesignList);

	if (curIndex > 1)
		curIndex--;

	_ccModel->reset();
	ui.tWCCTableView->selectRow(curIndex);
}

void CCTableDialog::slotClickColorButton(bool isChenile)
{
	ui.wDNormal->updateColorButtons();
	ui.wDChenile->updateColorButtons();
}

void CCTableDialog::modifyModelData(const QList<NeedleSet>& TempDesignList)
{
	for (int i = 0; i < _ccModel->rowCount(); i++)
	{
		_ccModel->getData()[i].Needle = TempDesignList[i].Needle;
		_ccModel->getData()[i].Group  = TempDesignList[i].Group;
		_ccModel->getData()[i].Height = TempDesignList[i].Height;
		_ccModel->getData()[i].Option = TempDesignList[i].Option;
	}
}

int CCTableDialog::colorToInt(QColor colorValue, bool isAlpha)
{
	int a = colorValue.alpha() << 24;
	int r = colorValue.red() << 16;
	int g = colorValue.green() << 8;
	int b = colorValue.blue();

	if (isAlpha)
		return a + r + g + b;

	return r + g + b;
}