#include "DialogFiltering.h"

DialogFiltering::DialogFiltering(const EbdFileInfo& ebdInfo, QWidget *parent)
	: IDialogDesign(ebdInfo, parent)
{
	ui.setupUi(this);
}

DialogFiltering::~DialogFiltering()
{
}
