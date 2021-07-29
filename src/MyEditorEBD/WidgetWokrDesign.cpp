#include "MakeDesign.h"
#include "WidgetWokrDesign.h"

#include <QBuffer>
#include <qmimedata.h>
#include <QMouseEvent>

WidgetWokrDesign::WidgetWokrDesign(const QString& fileName, QWidget* parent)
	: _fileName(fileName), QWidget(parent)
{
	ui.setupUi(this);
	 
	_readFile = Q_NULLPTR;
	_ebdFileInfo.dParts = Q_NULLPTR;

	initializeDrawing();
	initConnection();
}

WidgetWokrDesign::~WidgetWokrDesign()
{
	if (_ebdFileInfo.dParts != Q_NULLPTR)
	{
		delete _ebdFileInfo.dParts;
		_ebdFileInfo.dParts = Q_NULLPTR;
	}

	if (_readFile != Q_NULLPTR)
	{
		delete _readFile;
		_readFile = Q_NULLPTR;
	}

	disconnect(Control::instance(), &Control::sigFileHasDropped, this, &WidgetWokrDesign::sigFileHasDropped);
}

void WidgetWokrDesign::initializeDrawing()
{ 
	ui.grViewSewing->setVisibleGrid(false);
	ui.grViewSewing->setVisibleAxis(false);
	ui.grViewSewing->setEditStitches(false);
	ui.grViewSewing->setReArrangeObjects(false);
}
 
void WidgetWokrDesign::initConnection()
{
	//connect(Control::instance(), &Control::sigFileHasDropped, this, &WidgetWokrDesign::sigFileHasDropped);
	connect(Control::instance(), SIGNAL(sigDesignDataChanged()), this, SIGNAL(sigDesignDataChanged()));
}

bool WidgetWokrDesign::drawDesign(int id)
{
	FileSuffix suffix = Control::instance()->fileSuffix(_fileName);
	switch (suffix)
	{
		case CommonDef::Sst:
			_readFile = new ReadSstFile(_fileName);
			break;
		case CommonDef::Ebd:
			_readFile = new ReadEbdFile(_fileName);
			break;
		case CommonDef::Dst:
			_readFile = new ReadDstFile(_fileName);
			break;
		case CommonDef::Tbf:
			_readFile = new ReadTbfFile(_fileName);
			break;
		default: 
			break;
	}

	_ebdFileInfo.changed = false;
	if (_readFile->read(_ebdFileInfo, false) == false)
	{
		qDebug() << _readFile->errorString();
		return false;
	}
	
	if (suffix != CommonDef::Ebd)
	{
		ReadFile* readFile = Q_NULLPTR;
		if (suffix == CommonDef::Dst)
		{
			readFile = new ReadDstFile(_fileName);
		}
		else if (suffix == CommonDef::Sst)
		{
			readFile = new ReadSstFile(_fileName);
		}
		else if (suffix == CommonDef::Tbf)
		{
			readFile = new ReadTbfFile(_fileName);
		}

		EbdFileInfo ebdFileInfo;
		if (readFile->read(ebdFileInfo, true))
		{
			MakeDesign thumbNail;
			thumbNail.makeThumbnail(&ebdFileInfo); 
		}

		_ebdFileInfo.ebdHeader.ThumbNailData = ebdFileInfo.ebdHeader.ThumbNailData;
		_ebdFileInfo.ebdHeader.ThumbNailSize = ebdFileInfo.ebdHeader.ThumbNailData.count(); 

		if (readFile != Q_NULLPTR)
		{
			delete readFile;
			readFile = Q_NULLPTR;
		}

	}

	_ebdFileInfo.navigateId = id;
	_ebdFileInfo.strFile = _fileName;
	ui.grViewSewing->setEbdInfo(&_ebdFileInfo);

	return true;
}
 
void WidgetWokrDesign::setStitchColor(const QList<QColor>& cList)
{
	//ui.wdWork->setStitchColor(cList);
	ui.grViewSewing->setStitchColor(cList);
}

EbdFileInfo& WidgetWokrDesign::getFileInfo()
{
	return _ebdFileInfo;
}

void WidgetWokrDesign::setReArrangeObjects(bool clicked)
{
	//ui.wdWork->setReArrangeObjects(clicked);
	ui.grViewSewing->setReArrangeObjects(clicked);
}

void WidgetWokrDesign::setEditStitches(bool clicked)
{
	//ui.wdWork->setEditStitches(clicked);
	ui.grViewSewing->setEditStitches(clicked);
}

void WidgetWokrDesign::setGridVisible(bool clicked)
{
	//ui.wdWork->setVisibleGrid(clicked);
	ui.grViewSewing->setVisibleGrid(clicked);
}

void WidgetWokrDesign::setAxisVisible(bool clicked)
{
	//ui.wdWork->setVisibleAxis(clicked);
	ui.grViewSewing->setVisibleAxis(clicked);
}

void WidgetWokrDesign::setPointingPoint(bool click)
{
	//ui.wdWork->setPointingPoint(click);
	ui.grViewSewing->setPointingPoint(click);
}

bool WidgetWokrDesign::getVisibleAxis() const
{
	//return ui.wdWork->getVisibleAxis();
	return ui.grViewSewing->getVisibleAxis();
}

bool WidgetWokrDesign::getVisibleGrid() const
{
	//return ui.wdWork->getVisibleGrid();
	return ui.grViewSewing->getVisibleGrid();
}

bool WidgetWokrDesign::getReArrangeObjects() const
{
	//return ui.wdWork->getReArrangeObjects();
	return ui.grViewSewing->getReArrangeObjects();
}

bool WidgetWokrDesign::getEditStitches() const
{
	return ui.grViewSewing->getEditStitches();
}

bool WidgetWokrDesign::getVisiblePointingPoint() const
{
	return ui.grViewSewing->getPointingPoint();
}

LinePoint WidgetWokrDesign::getLinePoint(int row)
{
	int lineRow = 0;

	for(int i = 0;  i < _ebdFileInfo.dParts->count(); i++)
	{
		const DesignPart& dp = _ebdFileInfo.dParts->at(i);
		for (int j = 0; j < dp.points.count(); j++)
		{
			if (lineRow == row)
			{
				return dp.points[j];
			}

			lineRow++;
		}
	}

	return LinePoint();
}

int WidgetWokrDesign::getRowOfMovingPart()
{
	int row = 0;
	for (int i = 0; i < _ebdFileInfo.dParts->count(); i++)
	{
		const DesignPart& dp = _ebdFileInfo.dParts->at(i);
		if (dp.isActive) break;
		//for (int j = 0; j < dp.points.count(); j++) {}
		row += dp.points.count();
	}
	
	return (row == _ebdFileInfo.getCountOfData())? 0 : row;
}

void WidgetWokrDesign::setClickPointInfo(const LinePoint& point)
{
	//ui.wdWork->setClickPointInfo(point, true);
	ui.grViewSewing->setClickPointInfo(point, true);
}

void WidgetWokrDesign::slotClickDesign2(const LinePoint& point)
{
	emit sigClickDesign(point);
}
 
void WidgetWokrDesign::closeEvent(QCloseEvent* event)
{
	//Control::instance()->removePixmapFromNavigationList(_ebdFileInfo.navigateId);
	emit sigWorkDesignClosing(this);
}