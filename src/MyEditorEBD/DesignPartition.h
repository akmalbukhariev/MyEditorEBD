#pragma once

#include <qmath.h>
#include <QObject>

#include "Control.h"
#include "SewingGrid.h"

class DesignPartition : public QObject
{
	Q_OBJECT

public:
	DesignPartition(DataDesign* data, QObject* parent = Q_NULLPTR);
	~DesignPartition();

	//Set sn axis in order to convert points to the pixel.
	void setAxis(SewingGrid* xAxis, SewingGrid* yAxis);

	//Set a needle color
	void setStitchColor(const QList<QColor>& stitchColor);

	//Get a data.
	DataDesign* data() { return _data; }
	DataDesign* dataChanged() { return _dataChanged; }

	//Get a boundary of design.
	const QRect& getDesignRect() const
	{
		return _designRect;
	}

	//Calculate a partion of the design
	//void calcPartition();
	void calcPartition();

	//Get a calculated partion list.
	const QList<DesignPart>& getPartitions() const
	{
		return _dPartList;
	}

	//Get selected area.
	DesignPart getSelectedArea(const QPoint& point);

	//Update a Design Part.
	void updateDesignPart(const QPoint& movePoint, const QPoint& clickPoint, DesignPart& dPart);

	//Remove a Design Part. 
	void removeDesignPart(const DesignPart& dPart);

private:
	int _finishedThCount;

	QRect _designRect;

	SewingGrid* _xAxis;
	SewingGrid* _yAxis;

	SewingGrid* _xRealAxis;
	SewingGrid* _yRealAxis;

	QList<QColor> _stitchColor;
	QList<DesignPart> _dPartList;

	DataDesign* _data;
	DataDesign* _dataChanged;
};