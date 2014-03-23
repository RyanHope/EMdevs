#include "SaccadeExec.h"
#include "ansi.h"
using namespace std;
using namespace adevs;

const int SaccadeExec::execute = 0;
const int SaccadeExec::fixation = 1;

SaccadeExec::SaccadeExec(std::mt19937& twister):Atomic<IO_Type>(),
		_mean(40),
		_stdev(13),
		_time(0.0),
		_threshold(DBL_MAX),
		_saccade(NULL)
{
	_twister = twister;
}

double SaccadeExec::ta()
{
	return _threshold;
}

void SaccadeExec::delta_int()
{
}

void SaccadeExec::delta_ext(double e, const Bag<IO_Type>& xb)
{
	std::gamma_distribution<double> dist(((_mean*_mean)/(_stdev*_stdev)),(_stdev*_stdev)/_mean);

	_time += e;

	_saccade = new Saccade(*((*xb.begin()).value));
	_threshold = dist(_twister);

	//printf(BLUE "%f\t    SaccadeExec: saccade[id=%d] START\n" RESET, _time, _saccade->id);

}

void SaccadeExec::delta_conf(const Bag<IO_Type>& xb)
{
	delta_int();
	delta_ext(0.0,xb);
}

void SaccadeExec::output_func(Bag<IO_Type>& yb)
{
	IO_Type output(fixation, _saccade);
	yb.insert(output);
	_time += _threshold;
	_threshold = DBL_MAX;
	//printf(GREEN "%f\t    SaccadeExec: saccade[id=%d] END\n" RESET, _time, _saccade->id);
}

void SaccadeExec::gc_output(Bag<IO_Type>& g)
{
	Bag<IO_Type>::iterator i;
	for (i = g.begin(); i != g.end(); i++)
		delete (*i).value;
	_saccade = NULL;
}

SaccadeExec::~SaccadeExec()
{
}
