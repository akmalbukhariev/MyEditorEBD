#include "DialogRepeat.h"

DialogRepeat::DialogRepeat(const EbdFileInfo& ebdInfo, QWidget* parent)
	: IDialogDesign(ebdInfo, parent)
{
	ui.setupUi(this);
}

DialogRepeat::~DialogRepeat()
{

}
