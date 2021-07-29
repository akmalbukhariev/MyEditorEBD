#pragma once

#include <QDialog>

#include "IDialogDesign.h"
#include "ui_DialogStitchDivide.h"

class DialogStitchDivide : public IDialogDesign
{
	Q_OBJECT

public:
	DialogStitchDivide(const EbdFileInfo& ebdInfo, QWidget* parent = Q_NULLPTR);
	~DialogStitchDivide();

private:
	Ui::DialogStitchDivide ui;
};
