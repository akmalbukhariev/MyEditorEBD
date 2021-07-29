#include "IDialogDesign.h"

IDialogDesign::IDialogDesign(const EbdFileInfo& ebdInfo, QWidget *parent)
	:_ebdInfo(ebdInfo), QDialog(parent)
{

}

IDialogDesign::~IDialogDesign()
{

}
