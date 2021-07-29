#include "DesignPropertiesDialog.h"

#include <QFileInfo>

DesignPropertiesDialog::DesignPropertiesDialog(EbdFileInfo* ebdInfo, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setInfo(ebdInfo);

	connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(close()));
}

DesignPropertiesDialog::~DesignPropertiesDialog()
{
}

void DesignPropertiesDialog::setInfo(EbdFileInfo* ebdInfo)
{
	ui.lbFileName->setText(ebdInfo->strFile + "/" + QString((char*)ebdInfo->ebdHeader.FileName));
	ui.lbImage->setPixmap(ebdInfo->thumbNail);
	ui.lbDesign->setText(QString((char*)ebdInfo->ebdHeader.DesignName));
	//ui.lbSize->setText(ebdInfo->ebdHeader.Si)
	ui.lbTotalStitch->setText(QString(ebdInfo->ebdHeader.StitchCount));
	//ui.lbColor->setText(QString(ebdInfo->ebdHeader.ColorSize));
	ui.lbJump->setText(QString(ebdInfo->ebdHeader.JumpNum));
}
