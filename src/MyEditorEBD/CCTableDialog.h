#pragma once

#include <QDialog>

#include "CCTableModel.h"
#include "ui_CCTableDialog.h"

class CCTableDialog : public QDialog
{
	Q_OBJECT

public:
	CCTableDialog(EbdFileInfo* ebdInfo, QWidget* parent = Q_NULLPTR);
	~CCTableDialog();

private:
	void initUI();
	void initTable();
	void initConnection();
	void initNeedleColor();
	void initCCTableVIew();

	void modifyModelData(const QList<NeedleSet>& TempDesignList);
	int colorToInt(QColor colorValue, bool isAlpha);

private slots:
	void slotSaveButton();
	void slotInitButton();
	void slotAddCC();
	void slotRemoveCC();

	void slotClickColorButton(bool isChenile);

private:
	Ui::CCTableDialog ui;

	EbdFileInfo* _ebdInfo;
	CCTableModel* _ccModel;
};