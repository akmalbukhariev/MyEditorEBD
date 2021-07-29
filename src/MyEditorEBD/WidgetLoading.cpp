#include "WidgetLoading.h"

#include <QMovie>
#include <QStyle>
#include <QDesktopWidget>

WidgetLoading::WidgetLoading(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	
	initUI();
}

WidgetLoading::~WidgetLoading()
{
}

void WidgetLoading::initUI()
{
	setMinimumWidth(83);
	setMaximumWidth(83);
	QRect scr = QApplication::desktop()->screenGeometry();
	move(scr.center() - rect().center());

	QMovie* m = new QMovie("Resources/working.gif");
	ui.lbLoadingGif->setMovie(m);
	m->start();
}

void WidgetLoading::showEvent(QShowEvent* event)
{
	//QRect parentRect(parentWidget()->mapToGlobal(QPoint(0, 0)), parentWidget()->size());
	//move(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), parentRect).topLeft());

	/*QPoint dialogCenter = mapToGlobal(rect().center());
	QPoint parentWindowCenter = parentWidget()->window()->mapToGlobal(parentWidget()->window()->rect().center());
	move(parentWindowCenter - dialogCenter);*/

	/*move(parentWidget()->window()->frameGeometry().topLeft() +
		parentWidget()->window()->rect().center() - rect().center());*/

	//move(parentWidget()->geometry().center());
}