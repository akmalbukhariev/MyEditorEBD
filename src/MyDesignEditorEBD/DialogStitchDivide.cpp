#include "DialogStitchDivide.h"

DialogStitchDivide::DialogStitchDivide(const EbdFileInfo& ebdInfo, QWidget *parent)
	: IDialogDesign(ebdInfo, parent)
{
	ui.setupUi(this);
}

DialogStitchDivide::~DialogStitchDivide()
{
}
