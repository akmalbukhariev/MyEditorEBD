#include "Control.h"
#include "DrawDesign.h"

DrawDesign::DrawDesign(QObject* parent)
	: QObject(parent)
{
	_THUM_DESIGN_W = 91;
	_THUM_DESIGN_H = 97;
	_DRAWING_MARGIN = 15;
}

DrawDesign::~DrawDesign()
{
}

void DrawDesign::makeThumbnail(EbdFileInfo* ebdInfo)
{
	int ZX, ZY;
	int SX, SY;

	float scale = SetScale(ebdInfo, ZX, ZY, SX, SY);

	int PX = ZX;
	int PY = ZY;

	int AX = 0;
	int AY = 0;

	ebdInfo->thumbNail = QPixmap(_THUM_DESIGN_W, _THUM_DESIGN_H);
	ebdInfo->thumbNail.fill(Qt::white);
	QPainter painter(&ebdInfo->thumbNail);

	int colorIndex = 0;
	char sequinFlag = 0;

	for (int stitch = 0; stitch < ebdInfo->points.count(); stitch++)
	{
		int XX = (qint32)(ebdInfo->points[stitch].point.x());
		int YY = (qint32)(ebdInfo->points[stitch].point.y());

		char func = (char)(ebdInfo->points[stitch].func & STITCH::FUNCTION_FILTER);

		QColor pen;
		if (colorIndex < 15)
		{
			pen = ebdInfo->defaultPalettes[colorIndex];
		}
		else
		{
			colorIndex = 0;
		}

		switch (func)
		{
			case STITCH::NORMAL_CODE:
			case STITCH::STOP_CODE:
			case STITCH::END_CODE:
				StitchDraw(pen, &painter, XX, -YY, scale, SX, SY, PX, PY, AX, AY, PX, PY, AX, AY);
				break;
			case STITCH::JUMP_CODE:
				JumpDraw(pen, &painter, XX, -YY, scale, SX, SY, PX, PY, AX, AY, PX, PY, AX, AY);
				break;
			case STITCH::CC_CODE:
				colorIndex++;
				//DrawDesign.SetStitchColor(colorIndex, out color, out pen, needleColor, needleSet, needleSet.Length);
				StitchDraw(pen, &painter, XX, -YY, scale, SX, SY, PX, PY, AX, AY, PX, PY, AX, AY);
				break;
			case STITCH::SQSTART_CODE:
				sequinFlag = 1;
				StitchDraw(pen, &painter, XX, -YY, scale, SX, SY, PX, PY, AX, AY, PX, PY, AX, AY);
				break;
			case STITCH::SQEND_CODE:
				sequinFlag = 0;
				StitchDraw(pen, &painter, XX, -YY, scale, SX, SY, PX, PY, AX, AY, PX, PY, AX, AY);
				break;
			case STITCH::FRONTSQ_CODE:
				if (sequinFlag != 0)
					SequinDraw(pen, &painter, XX, -YY, STITCH::FRONT_SEQUIN, true, scale, SX, SY, PX, PY, AX, AY, PX, PY, AX, AY);
				else
					StitchDraw(pen, &painter, XX, -YY, scale, SX, SY, PX, PY, AX, AY, PX, PY, AX, AY);
				break;
			case STITCH::REARSQ_CODE:
				if (sequinFlag != 0)
					SequinDraw(pen, &painter, XX, -YY, STITCH::REAR_SEQUIN, true, scale, SX, SY, PX, PY, AX, AY, PX, PY, AX, AY);
				else
					StitchDraw(pen, &painter, XX, -YY, scale, SX, SY, PX, PY, AX, AY, PX, PY, AX, AY);
				break;
			case STITCH::ALLSQ_CODE:
				if (sequinFlag != 0)
					SequinDraw(pen, &painter, XX, -YY, STITCH::ALL_SEQUIN, true, scale, SX, SY, PX, PY, AX, AY, PX, PY, AX, AY);
				else
					StitchDraw(pen, &painter, XX, -YY, scale, SX, SY, PX, PY, AX, AY, PX, PY, AX, AY);
				break;
			default:
				break;
		}

		if (func == STITCH::END_CODE)
		{
			break;
		}
	} 
} 

float DrawDesign::SetScale(EbdFileInfo* ebdInfo, int& ZX, int& ZY, int& SX, int& SY)
{
	float scale = 0.0f;

	float dstW, dstH, scaleW, scaleH;
	int MarginX, MarginY;

	short absMinusX = 0;
	short absMinusY = 0;

	absMinusX = qAbs(ebdInfo->ebdHeader.Minus_x);
	absMinusY = qAbs(ebdInfo->ebdHeader.Minus_y);

	dstW = (float)(ebdInfo->ebdHeader.Plus_x + absMinusX);//������ ���� ���� ���
	dstH = (float)(ebdInfo->ebdHeader.Plus_y + absMinusY);//������ ���� ���� ���

	// ȭ�� VS ������ ���� ���� ���� ���
	scaleW = (float)((float)(_THUM_DESIGN_W - (_DRAWING_MARGIN * 2))) / dstW; //������ ���� ��� ȭ�� ���� �ȼ��� ���� ���(�̹��� ���� ������ ���)
	scaleH = (float)((float)(_THUM_DESIGN_H - (_DRAWING_MARGIN * 2))) / dstH; //������ ���� ��� ȭ�� ���� �ȼ��� ���� ���(�̹��� ���� ������ ���)

	 // �� ���� ��ҵǴ� �� ����
	scale = qMin(scaleW, scaleH); //����, ���� ������ ���� ���� ���� ����(���� ������ ���� ��� �̹��� ���� Ȯ��, ��� ����)

	// calculate mm per pixel for zoom step
	if (scale == scaleW)
		_MMperPixel = (float)(dstW / (double)_THUM_DESIGN_W); //�ȼ� �ϳ��� ǥ���ϴ� millimeter ���
	else
		_MMperPixel = (float)(dstH / (double)_THUM_DESIGN_H);

	// LCD ȭ��� ������ ũ�� ���
	scaleW = (float)(dstW * scale); //�������� ���� �ϴ� ���� �ȼ��� ���
	scaleH = (float)(dstH * scale);//�������� ���� �ϴ� ���� �ȼ��� ���

	// Draw ���� pointer calcurator
	MarginX = (int)((_THUM_DESIGN_W - scaleW) / 2.0); //�¿� �� ���� �ȼ��� ��� (�� ���� ȭ�� �ȼ��� - �������� ���� �ϴ� �ȼ��� / 2)
	MarginY = (int)((_THUM_DESIGN_H - scaleH) / 2.0); //���� �� ���� �ȼ��� ��� (�� ���� ȭ�� �ȼ��� - �������� �����ϴ� �ȼ��� / 2)

	//LCD ȭ��� �׸��� ������ ���
	double dX = qRound((double)absMinusX);
	double dY = qRound((double)ebdInfo->ebdHeader.Plus_y);
	int zeroX = dX; // pattern coord OX//���� ũ���� �����ο��� ���� ������ ���ϱ�
	int zeroY = dY; // pattern coord OY//���� ũ���� �����ο��� ���� ������ ���ϱ�

	float fX = (float)MarginX / scale;
	float fY = (float)MarginY / scale;

	SX = MarginX;
	SY = MarginY;

	ZX = zeroX;
	ZY = zeroY;

	return scale;
}

void DrawDesign::StitchDraw(const QColor& pen, QPainter* g, int DX, int DY, float scale, int sX, int sY,
								  int oPX, int oPY, int oAX, int oAY,
								  int& pX, int& pY, int& aX, int& aY)
{
	QPoint oldXY = PatternPointToScreenPoint(QPoint(oPX, oPY), scale, sX, sY);
	QPoint newXY = PatternPointToScreenPoint(QPoint((oPX + DX), (oPY + DY)), scale, sX, sY);

	g->setPen(QPen(pen));
	g->drawLine(oldXY.x(), oldXY.y(), newXY.x(), newXY.y());

	oPX += DX; oPY += DY;
	oAX += DX; oAY -= DY;

	pX = oPX; pY = oPY; aX = oAX; aY = oAY;
}

void DrawDesign::JumpDraw(const QColor& pen, QPainter* g, int DX, int DY, float scale, int sX, int sY,
								int oPX, int oPY, int oAX, int oAY,
								int& pX, int& pY, int& aX, int& aY)
{
	QPoint oldXY = PatternPointToScreenPoint(QPoint(oPX, oPY), scale, sX, sY);
	QPoint newXY = PatternPointToScreenPoint(QPoint((oPX + DX), (oPY + DY)), scale, sX, sY);

	QPen dotPen;
	dotPen.setColor(pen);
	dotPen.setStyle(Qt::DashLine);
	g->drawLine( oldXY.x(), oldXY.y(), newXY.x(), newXY.y());
	dotPen.setStyle(Qt::SolidLine);

	oPX += DX; oPY += DY;
	oAX += DX; oAY -= DY;

	pX = oPX; pY = oPY; aX = oAX; aY = oAY;
}

void DrawDesign::SequinDraw(const QColor& pen, QPainter* g, int DX, int DY, ushort type, bool for_back,
								  float scale, int sX, int sY, int oPX, int oPY, int oAX, int oAY,
								  int& pX, int& pY, int& aX, int& aY)
{
	QPoint oldXY = PatternPointToScreenPoint(QPoint(oPX, oPY), scale, sX, sY);
	QPoint newXY = PatternPointToScreenPoint(QPoint((oPX + DX), (oPY + DY)), scale, sX, sY);

	// 30 = 3mm Sequin
	// 50 = 5mm Sequin

	int smallSQ = (qint32)((float)30 * scale);
	int largeSQ = (qint32)((float)50 * scale);

	if (smallSQ == 0)
		smallSQ = 1;

	if (largeSQ == 0)
		largeSQ = 1;

	if (!for_back)
	{
		g->setPen(QPen(pen));
		if (type == STITCH::FRONT_SEQUIN)
			g->drawEllipse(newXY.x() - (smallSQ / 2), newXY.y() - (smallSQ / 2), smallSQ, smallSQ);
		else if (type == STITCH::REAR_SEQUIN)
			g->drawEllipse(newXY.x() - (largeSQ / 2), newXY.y() - (largeSQ / 2), largeSQ, largeSQ);
		else if (type == STITCH::ALL_SEQUIN)
		{
			g->drawEllipse(newXY.x() - (smallSQ / 2), newXY.y() - (smallSQ / 2), smallSQ, smallSQ);
			g->drawEllipse(newXY.x() - (largeSQ / 2), newXY.y() - (largeSQ / 2), largeSQ, largeSQ);
		}

		g->drawLine(oldXY.x(), oldXY.y(), newXY.x(), newXY.y());

		oPX += DX; oPY += DY;
		oAX += DX; oAY -= DY;
	}
	else
	{
		oPX += DX; oPY += DY;
		oAX += DX; oAY -= DY;

		if (type == STITCH::FRONT_SEQUIN)
			g->drawEllipse(newXY.x() - (smallSQ / 2), newXY.y() - (smallSQ / 2), smallSQ, smallSQ);
		else if (type == STITCH::REAR_SEQUIN)
			g->drawEllipse(newXY.x() - (largeSQ / 2), newXY.y() - (largeSQ / 2), largeSQ, largeSQ);
		else if (type == STITCH::ALL_SEQUIN)
		{
			g->drawEllipse(oldXY.x(), oldXY.y(), smallSQ, smallSQ);
			g->drawEllipse(oldXY.x(), oldXY.y(), largeSQ, largeSQ);
		}
	}
	pX = oPX; pY = oPY; aX = oAX; aY = oAY;
}

QPoint DrawDesign::PatternPointToScreenPoint(QPoint point, float scale, int sX, int sY)
{
	int cX = 0;
	int cY = 0;
	float currentX = (float)point.x() * scale;
	float currentY = (float)point.y() * scale;
	try 
	{
		cX = (qint32)(qRound((double)currentX + 0.05 + (double)sX));
		cY = (qint32)(qRound((double)currentY + 0.05 + (double)sY));
	}
	catch(...){}

	return QPoint(cX, cY);
}