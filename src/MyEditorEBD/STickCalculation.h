#pragma once

#include <QVector>

#include "CommonDef.h"

using namespace CommonDef;

class STickCalculation
{
public:
	STickCalculation();
	~STickCalculation();

	/*Calculate the ticks vector while the grid modify.*/
	static QVector< double > getTicks(const SAxisRange& axisRange);

private:

	static QVector<double> createTickVector(double tickStep, const SAxisRange& range);
	static void trimTicks(const SAxisRange& range, QVector<double> &ticks, bool keepOneOutlier);
	static double getTickStep(const SAxisRange& range);
	static double cleanMantissa(double input);
	static double getMantissa(double input, double* magnitude);
	static double pickClosest(double target, const QVector<double>& candidates);
};
