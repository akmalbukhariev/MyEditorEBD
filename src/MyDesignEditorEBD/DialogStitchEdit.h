#pragma once

#include <QDialog>

#include "IDialogDesign.h"
#include "ui_DialogStitchEdit.h"

class DialogStitchEdit : public IDialogDesign
{
	Q_OBJECT

public:
	DialogStitchEdit(const EbdFileInfo& ebdInfo, QWidget *parent = Q_NULLPTR);
	~DialogStitchEdit();

private:
	Ui::DialogStitch ui;
};
