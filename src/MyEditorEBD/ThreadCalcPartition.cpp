#include "ThreadCalcPartition.h"

ThreadCalcPartition::ThreadCalcPartition(DataDesign* data, int startIndex, int endIndex, QObject* parent)
	:_data(data), QThread(parent)
{
	_startIndex = startIndex;
	_endIndex = endIndex;

	_xAxis = nullptr;
	_yAxis = nullptr;
}

ThreadCalcPartition::~ThreadCalcPartition()
{

}

void ThreadCalcPartition::run()
{
	if (_xAxis == nullptr || _yAxis == nullptr) return;

	for (int i = _startIndex; i < _endIndex; i++)
	{
		DesignPart dPart = (*_data)[i];

		for (int j = 0; j < dPart.points.count(); j++)
		{
			LinePoint& p = dPart.points[j];

			float wX1 = _xAxis->coordToPixel(p.startP.x());
			float wY1 = _yAxis->coordToPixel(p.startP.y());

			float wX2 = _xAxis->coordToPixel(p.endP.x());
			float wY2 = _yAxis->coordToPixel(p.endP.y());

			p.startP.setX(wX1);
			p.startP.setY(wY1);

			p.endP.setX(wX2);
			p.endP.setY(wY2);
		}

		dPart.calcBorder();
		_result.append(dPart);
	}
}
