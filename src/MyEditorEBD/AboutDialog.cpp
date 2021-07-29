#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.btnOk, &QPushButton::clicked, this, &AboutDialog::close);
}

AboutDialog::~AboutDialog()
{

}
