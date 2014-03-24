#include "SaccadeTargetSelect.h"
#include "ansi.h"
using namespace std;
using namespace adevs;

#include "Rmath.h"

const int SaccadeTargetSelect::labile = 0;
const int SaccadeTargetSelect::nonlabile = 1;

SaccadeTargetSelect::SaccadeTargetSelect(double mean, double stdev):Atomic<IO_Type>(),
		_time(0.0),
		_threshold(DBL_MAX),
		_saccade(NULL)
{
	_mean = mean;
	_stdev = stdev;
}

double SaccadeTargetSelect::ta()
{
	return _threshold;
}

void SaccadeTargetSelect::delta_int()
{
}

void SaccadeTargetSelect::delta_ext(double e, const Bag<IO_Type>& xb)
{
	_time += e;
	Saccade* saccade = new Saccade(*((*xb.begin()).value));
	if (_saccade) {
		saccade->cancelations = ++_saccade->cancelations;
		saccade->labile_start = _saccade->labile_start;
		//printf(RED "%f\t  SaccadeTargetSelect: Canceling saccade[id=%d|%d]\n" RESET, _time, _saccade->id, _saccade->cancelations);
	} else {
		saccade->labile_start = _time;
	}
	//printf("%f\t  SaccadeTargetSelect: Starting new labile programming\n", _time);
	_saccade = saccade;
	_threshold = ::Rf_rgamma(((_mean*_mean)/(_stdev*_stdev)),(_stdev*_stdev)/_mean);

	//printf("%f\t  SaccadeTargetSelect: Next event at %f\n", _time, _time+_threshold);
}

void SaccadeTargetSelect::delta_conf(const Bag<IO_Type>& xb)
{
	delta_int();
	delta_ext(0.0,xb);
}

void SaccadeTargetSelect::output_func(Bag<IO_Type>& yb)
{
	IO_Type output(nonlabile, _saccade);
	yb.insert(output);
	_time += _threshold;
	_threshold = DBL_MAX;
	//printf("%f\t  SaccadeTargetSelect: Labile programming complete\n", _time);
}

void SaccadeTargetSelect::gc_output(Bag<IO_Type>& g)
{
	Bag<IO_Type>::iterator i;
	for (i = g.begin(); i != g.end(); i++)
		delete (*i).value;
	_saccade = NULL;
}

SaccadeTargetSelect::~SaccadeTargetSelect()
{
}
