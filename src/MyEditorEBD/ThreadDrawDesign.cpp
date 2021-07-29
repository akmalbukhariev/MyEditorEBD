#include "ThreadDrawDesign.h"

ThreadDrawDesign::ThreadDrawDesign(DesignPartition* partition, int startIdex, int endIndex, QObject* parent)
	:_partition(partition), QThread(parent)
{
	_startIndex = startIdex;
	_endIndex = endIndex;
}

ThreadDrawDesign::~ThreadDrawDesign()
{

}

void ThreadDrawDesign::run()
{
	QPen dotPen;
	dotPen.setStyle(Qt::DotLine);

	LinePoint tempPoint = LinePoint();

	for (int i = _startIndex; i < _endIndex; i++)
	{
		DesignPart& dPart = (*_partition->dataChanged())[i];

		for (int j = 0; j < dPart.points.count(); j++)
		{
			const LinePoint& lPoint = dPart.points[j];
			switch (lPoint.type)
			{
			case NORMAL_CODE:
				_painter->setPen(dPart.lineColor);
				break;
			case JUMP_CODE:
				dotPen.setColor(dPart.lineColor.color());
				_painter->setPen(dotPen);
				break;
			}

			_painter->drawLine(lPoint.startP, lPoint.endP);
			tempPoint = lPoint;
		}

		if (i + 1 < _partition->dataChanged()->count())
		{
			const DesignPart& tD = (*_partition->dataChanged())[i + 1];
			if (tD.points.count() != 0)
			{
				_painter->drawLine(tempPoint.endP, tD.points[0].startP);
			}
		}

		if (dPart.isActive)
		{
			_painter->setPen(QPen(Qt::blue, 2));
			_painter->drawRect(dPart.border);
		}
	}
}