#pragma once

#include <qmath.h>
#include <QObject>

#include "CommonDef.h"

using namespace CommonDef;

class MakeDesign : public QObject
{
public:
	MakeDesign(QObject* parent = Q_NULLPTR);
	~MakeDesign();

	void makeThumbnail(EbdFileInfo* ebdInfo);

	bool write(EbdFileInfo& ebdInfo, const QString& writeFile);

private: 

	float SetScale(EbdFileInfo* ebdInfo, int& ZX, int& ZY, int& SX, int& SY);
	
	void StitchDraw(const QColor& pen, QPainter* g, int DX, int DY, float scale, int sX, int sY, int oPX, int oPY, int oAX, int oAY, int& pX,  int& pY,  int& aX, int& aY);

	void JumpDraw(const QColor& pen, QPainter* g, int DX, int DY, float scale, int sX, int sY, int oPX, int oPY, int oAX, int oAY, int& pX, int& pY, int& aX, int& aY);

	void SequinDraw(const QColor& pen, QPainter* g, int DX, int DY, ushort type, bool for_back, float scale, int sX, int sY, int oPX, int oPY, int oAX, int oAY, int& pX, int& pY, int& aX, int& aY);

	QPoint PatternPointToScreenPoint(QPoint point, float scale, int sX, int sY);

	/*QList<LinePoint> getList(EbdFileInfo* ebdInfo);
	QList<LinePoint> getList(EbdFileInfo* ebdInfo, int& biggerRangeCount);*/

private:
	int _THUM_DESIGN_W;
	int _THUM_DESIGN_H;
	int _DRAWING_MARGIN;

	float _MMperPixel;
};
