#pragma once

#include <QDialog>

#include "CommonDef.h"
#include "ui_DesignPropertiesDialog.h"

using namespace CommonDef;

class DesignPropertiesDialog : public QDialog
{
	Q_OBJECT

public:
	DesignPropertiesDialog(EbdFileInfo* ebdInfo, QWidget* parent = Q_NULLPTR);
	~DesignPropertiesDialog();

private:
	void setInfo(EbdFileInfo* ebdInfo);

private:
	Ui::DesignPropertiesDialog ui;
};
