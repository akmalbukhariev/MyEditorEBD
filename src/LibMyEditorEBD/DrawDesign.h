#pragma once

#include <qmath.h>
#include <QObject>

#include "CommonDef.h"

using namespace CommonDef;

class LIBMYEDITOREBD_EXPORT DrawDesign : public QObject
{
public:
	DrawDesign(QObject* parent = Q_NULLPTR);
	~DrawDesign();

	void makeThumbnail(EbdFileInfo* ebdInfo);

private:
	float SetScale(EbdFileInfo* ebdInfo, int& ZX, int& ZY, int& SX, int& SY);
	
	void StitchDraw(const QColor& pen, QPainter* g, int DX, int DY, float scale, int sX, int sY,
					int oPX, int oPY, int oAX, int oAY,
					int& pX,  int& pY,  int& aX, int& aY);

	void JumpDraw(const QColor& pen, QPainter* g, int DX, int DY, float scale, int sX, int sY,
				  int oPX, int oPY, int oAX, int oAY,
				  int& pX, int& pY, int& aX, int& aY);

	void SequinDraw(const QColor& pen, QPainter* g, int DX, int DY, ushort type, bool for_back,
					float scale, int sX, int sY, int oPX, int oPY, int oAX, int oAY,
					int& pX, int& pY, int& aX, int& aY);

	QPoint PatternPointToScreenPoint(QPoint point, float scale, int sX, int sY);

private:
	float _MMperPixel;
	int _THUM_DESIGN_W;
	int _THUM_DESIGN_H;
	int _DRAWING_MARGIN;
};
