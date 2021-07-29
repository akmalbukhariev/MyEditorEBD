#include "STickCalculation.h"

#include <qmath.h>

STickCalculation::STickCalculation()
{
}

STickCalculation::~STickCalculation()
{
}

QVector< double > STickCalculation::getTicks(const SAxisRange& axisRange)
{
	QVector< double > ticks;
	double offset = getTickStep(axisRange);
	ticks = createTickVector(offset, axisRange);

	trimTicks(axisRange, ticks, true);
	trimTicks(axisRange, ticks, false);

	return ticks;
}

QVector<double> STickCalculation::createTickVector(double tickStep, const SAxisRange& range)
{
	QVector< double > result;
	double mTickOrigin = 0.0;
	qint64 firstStep = floor((range.lower - mTickOrigin) / tickStep);
	qint64 lastStep = ceil((range.upper - mTickOrigin) / tickStep);

	int tickCount = lastStep - firstStep + 1;
	if (tickCount < 0) tickCount = 0;
	result.resize(tickCount);

	for (int i = 0; i < tickCount; ++i)
		result[i] = mTickOrigin + (firstStep + i) * tickStep;
	return result;
}

void STickCalculation::trimTicks(const SAxisRange& range, QVector<double> &ticks, bool keepOneOutlier)
{
	bool lowFound = false;
	bool highFound = false;
	int lowIndex = 0;
	int highIndex = -1;

	for (int i = 0; i < ticks.size(); ++i)
	{
		if (ticks.at(i) >= range.lower)
		{
			lowFound = true;
			lowIndex = i;
			break;
		}
	}

	for (int i = ticks.size() - 1; i >= 0; --i)
	{
		if (ticks.at(i) <= range.upper)
		{
			highFound = true;
			highIndex = i;
			break;
		}
	}

	if (highFound && lowFound)
	{
		int trimFront = qMax(0, lowIndex - (keepOneOutlier ? 1 : 0));
		int trimBack = qMax(0, ticks.size() - (keepOneOutlier ? 2 : 1) - highIndex);
		if (trimFront > 0 || trimBack > 0)
			ticks = ticks.mid(trimFront, ticks.size() - trimFront - trimBack);
	}
	else
	{
		ticks.clear();
	}
}

double STickCalculation::getTickStep(const SAxisRange& range)
{
	int mTickCount = 5;
	double exactStep = (range.upper - range.lower) / (double)(mTickCount + 1e-10);

	return cleanMantissa(exactStep);
}

double STickCalculation::cleanMantissa(double input)
{
	double magnitude;
	const double mantissa = getMantissa(input, &magnitude);

	return pickClosest(mantissa, QVector< double >() << 1.0 << 2.0 << 2.5 << 5.0 << 10.0) * magnitude;
}

double STickCalculation::getMantissa(double input, double* magnitude)
{
	const double mag = qPow(10.0, qFloor(qLn(input) / qLn(10.0)));
	if (magnitude) *magnitude = mag;
	return input / mag;
}

double STickCalculation::pickClosest(double target, const QVector<double>& candidates)
{
	if (candidates.size() == 1)
		return candidates.first();
	QVector<double>::const_iterator it = std::lower_bound(candidates.constBegin(), candidates.constEnd(), target);
	if (it == candidates.constEnd())
		return *(it - 1);
	else if (it == candidates.constBegin())
		return *it;
	else
		return target - *(it - 1) < *it - target ? *(it - 1) : *it;
}