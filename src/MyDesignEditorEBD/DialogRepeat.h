#pragma once

#include <QDialog>

#include "IDialogDesign.h"
#include "ui_DialogRepeat.h"

class DialogRepeat : public IDialogDesign
{
	Q_OBJECT

public:
	DialogRepeat(const EbdFileInfo& ebdInfo, QWidget* parent = Q_NULLPTR);
	~DialogRepeat();

private:
	Ui::DialogRepeat ui;
};
