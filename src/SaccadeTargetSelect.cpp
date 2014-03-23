#include "SaccadeTargetSelect.h"
#include "ansi.h"
using namespace std;
using namespace adevs;

const int SaccadeTargetSelect::labile = 0;
const int SaccadeTargetSelect::nonlabile = 1;

SaccadeTargetSelect::SaccadeTargetSelect(std::mt19937& twister):Atomic<IO_Type>(),
		_mean(180),
		_stdev(45),
		_time(0.0),
		_threshold(DBL_MAX),
		_saccade(NULL)
{
	_twister = twister;
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
	std::gamma_distribution<double> dist(((_mean*_mean)/(_stdev*_stdev)),(_stdev*_stdev)/_mean);
	_time += e;
	if (_saccade) {
		//printf(RED "%f\t  SaccadeTargetSelect: Canceling saccade[id=%d]\n" RESET, _time, _saccade->id);
	}
	//printf("%f\t  SaccadeTargetSelect: Starting new labile programming\n", _time);

	_saccade = new Saccade(*((*xb.begin()).value));
	_threshold = dist(_twister);

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
