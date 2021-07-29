#include "WidgetDesignNavigator.h"

WidgetDesignNavigator::WidgetDesignNavigator(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

WidgetDesignNavigator::~WidgetDesignNavigator()
{

}

void WidgetDesignNavigator::addDesign(const QIcon& icon, const QString& iconFileName)
{
	ui.lsWidgetDesign->addDesign(icon, iconFileName);
}

void WidgetDesignNavigator::removeDesign(const QString& iconFileName)
{

}

void WidgetDesignNavigator::addItem(WidgetWokrDesign* design)
{
	ui.lsWidgetDesign->addDesign(design);
}

void WidgetDesignNavigator::selectItemFile(const QString& iconFileName)
{
	ui.lsWidgetDesign->selectItemFile(iconFileName);
}