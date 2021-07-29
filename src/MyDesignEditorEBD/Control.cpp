#include "Control.h"

Control* Control::_self = Q_NULLPTR;

Control::Control()
{
	_wLoading = new WidgetLoading();
}

Control* Control::instance()
{
	if (_self == Q_NULLPTR)
	{
		_self = new Control();
	}

	return _self;
}

Control::~Control()
{

}

void Control::showLoading(QWidget* parent)
{
	_thLoading = new ThreadLoading(_wLoading, this);
	_thLoading->start();
}

void Control::closeLoading()
{
	if (_thLoading != Q_NULLPTR)
	{
		_wLoading->close();
		delete _thLoading;
		_thLoading = Q_NULLPTR;
	}
}