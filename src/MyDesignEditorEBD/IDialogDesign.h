#pragma once

#include <QDialog>

#include "CommonDef.h"

using namespace CommonDef;

class IDialogDesign : public QDialog
{
	Q_OBJECT

public:
	IDialogDesign(const EbdFileInfo& ebdInfo, QWidget *parent =Q_NULLPTR);
	IDialogDesign() {}
	~IDialogDesign();

protected:
	EbdFileInfo _ebdInfo;
};
