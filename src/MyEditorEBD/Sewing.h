#ifndef SEWING_H
#define SEWING_H

#include <qmath.h>

#include "SewingGrid.h"
#include "DesignPartition.h"
 
class Sewing : public QObject
{
	Q_OBJECT
public:

	Sewing(SewingGrid* xAxis, SewingGrid* yAxis);
	~Sewing();

	//Set all data.
	void setData(DataDesign* data);

	//Get a Design partion.
	DesignPartition* designPart() const
	{
		return _partition;
	}

	//Set stitch count.
	void setStitchCount(int nCount)
	{
		_stCount = nCount;
	}

	//Set stitch color.
	void setStitchColor(const QColor& stColor, int needle);
	void setStitchColor(const QList<QColor>& cList);

	void setMenuButton(MenuButton btnMenu)
	{
		_btnMenu = btnMenu;
	}

	//Repaint
	void drawDesign(QPainter* painter);

	//Draw the border over the selected part
	void drawDesignPartBorder(QPoint& point, QPainter* painter);

	//Un activate the selected part.
	void unActivateSelectDesign(const QPoint& point);

	//Move a selected part
	void moveDesignPart(const QPoint& movePoint, const QPoint& clickPoint);

	//Make unactivate.
	void unActiveAllDesignParts();

private:
	void cleanColorTable();
	 
private:

	int _stCount;

	MenuButton _btnMenu;

	QPen _dotPen;
	QPen _linePen;

	QPainter* _painter;
	SewingGrid* _xAxis;
	SewingGrid* _yAxis;
	DesignPart _designPart;
	
	QList<QColor> _stitchColor;
	DesignPartition* _partition;
};

#endif // SEWING_H
