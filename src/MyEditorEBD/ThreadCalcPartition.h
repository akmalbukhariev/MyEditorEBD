#pragma once

#include "CommonDef.h"
#include "SewingGrid.h"

#include <QThread>

using namespace CommonDef;

class ThreadCalcPartition : public QThread
{
	Q_OBJECT

public:
	ThreadCalcPartition(DataDesign* data, int startIndex, int endIndex, QObject* parent = Q_NULLPTR);
	~ThreadCalcPartition();

	void setAxis(SewingGrid* xAxis, SewingGrid* yAxis)
	{
		_xAxis = xAxis;
		_yAxis = yAxis;
	}

	const QList<DesignPart>& result()
	{
		return _result;
	}

protected:
	void run() override;

private:
	int _startIndex;
	int _endIndex;

	SewingGrid* _xAxis;
	SewingGrid* _yAxis;

	DataDesign* _data;
	QList<DesignPart> _result;
};
