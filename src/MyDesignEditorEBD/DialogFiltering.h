#pragma once

#include <QDialog>

#include "IDialogDesign.h"
#include "ui_DialogFiltering.h"

class DialogFiltering : public IDialogDesign
{
	Q_OBJECT

public:
	DialogFiltering(const EbdFileInfo& ebdInfo, QWidget *parent = Q_NULLPTR);
	~DialogFiltering();

private:
	Ui::DialogFiltering ui;
};
