#include "DialogStitchEdit.h"

DialogStitchEdit::DialogStitchEdit(const EbdFileInfo& ebdInfo, QWidget *parent)
	: IDialogDesign(ebdInfo, parent)
{
	ui.setupUi(this);
}

DialogStitchEdit::~DialogStitchEdit()
{
}
