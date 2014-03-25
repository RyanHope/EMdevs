#include "Rmath.h"
#include "Rcpp.h"
#include "SaccadeMotorProgram.h"
#include "ansi.h"
using namespace std;
using namespace adevs;
using namespace Rcpp;

const int SaccadeMotorProgram::nonlabile = 0;
const int SaccadeMotorProgram::execute = 1;

bool sortNonLabile(const Saccade* a, const Saccade* b)
{
	return a->nonlabile_t < b->nonlabile_t;
}

SaccadeMotorProgram::SaccadeMotorProgram(double mean, double stdev):Atomic<IO_Type>(),
		_time(0.0),
		_threshold(DBL_MAX)
{
	_mean = mean;
	_stdev = stdev;
}

void SaccadeMotorProgram::delta_ext(double e, const Bag<IO_Type>& xb)
{
	_time += e;
	if (!_saccades.empty())
	{
		//Rcout << _time << " There are " << _saccades.size() << " saccades in the motor queue." << endl;
		list<Saccade*>::const_iterator si = _saccades.begin();
		for(; si != _saccades.end(); si++)
		{
			(*si)->nonlabile_t -= e;
		}
	}
	Bag<IO_Type>::const_iterator iter = xb.begin();
	for (; iter != xb.end(); iter++)
	{
		Saccade* s = new Saccade(*((*xb.begin()).value));
		s->labile_stop = _time;
		s->nonlabile_start = _time;
		s->nonlabile_t = ::Rf_rgamma(((_mean*_mean)/(_stdev*_stdev)),(_stdev*_stdev)/_mean);
		_saccades.push_back(s);
	}
	_saccades.sort(sortNonLabile);
	//printf("%f\t    SaccadeMotorProgram: Starting non-labile programming for saccade[id=%d]\n", _time, _saccade->id);
	//printf("%f\t    SaccadeMotorProgram: Next event at %f\n", _time, _time+_threshold);
}

void SaccadeMotorProgram::delta_int()
{
	_time += ta();
	_saccades.pop_front();
}

void SaccadeMotorProgram::delta_conf(const Bag<IO_Type>& xb)
{
	delta_int();
	delta_ext(0.0,xb);
}

void SaccadeMotorProgram::output_func(Bag<IO_Type>& yb)
{
	Saccade* s = _saccades.front();
	s->nonlabile_stop = _time + ta();
	IO_Type output(execute, s);
	yb.insert(output);
	//printf("%f\t    SaccadeMotorProgram: Non-labile programming complete\n", _time);
}

double SaccadeMotorProgram::ta()
{
	if (_saccades.empty()) return DBL_MAX;
	return _saccades.front()->nonlabile_t;
}

void SaccadeMotorProgram::gc_output(Bag<IO_Type>& g)
{
	Bag<IO_Type>::iterator i;
	for (i = g.begin(); i != g.end(); i++)
		delete (*i).value;
}

SaccadeMotorProgram::~SaccadeMotorProgram()
{
	list<Saccade*>::iterator i;
	for (i = _saccades.begin(); i != _saccades.end(); i++)
		delete *i;
}
