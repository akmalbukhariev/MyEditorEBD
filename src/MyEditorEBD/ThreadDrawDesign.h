#pragma once

#include <qmath.h>
#include <QThread>

#include "CommonDef.h"
#include "DesignPartition.h"

using namespace CommonDef;

class ThreadDrawDesign : public QThread
{
	Q_OBJECT

public:
	ThreadDrawDesign(DesignPartition* partition, int startIdex, int endIndex, QObject* parent = Q_NULLPTR);
	~ThreadDrawDesign();

	void setPainter(QPainter* painter)
	{
		_painter = painter;
	}

protected:
	void run() override;

private:
	int _startIndex;
	int _endIndex;

	QPainter* _painter;
	DesignPartition* _partition;
};