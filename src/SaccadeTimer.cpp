#include "Rmath.h"
#include "SaccadeTimer.h"
using namespace std;
using namespace adevs;

const int SaccadeTimer::labile = 1;

SaccadeTimer::SaccadeTimer(double mean_duration, int states):Atomic<IO_Type>(),
		_saccade(NULL),
		_threshold(0.0),
		_time(0.0),
		_n(0)
{
	_mean_duration = mean_duration;
	_states = states;
	delta_int();
}

double SaccadeTimer::ta()
{
	return _threshold;
}

void SaccadeTimer::delta_int()
{
	_saccade = new Saccade(++_n,_time);
	_threshold = 0;
	for(int i = 0; i < _states; ++i) _threshold -= (_mean_duration/_states)*std::log(1-::Rf_runif(0.0,1.0));
}

void SaccadeTimer::delta_ext(double e, const Bag<IO_Type>& xb)
{
}

void SaccadeTimer::delta_conf(const Bag<IO_Type>& xb)
{
	delta_int();
}

void SaccadeTimer::output_func(Bag<IO_Type>& yb)
{
	_time += _threshold;
	_saccade->timer_stop = _time;
	IO_Type output(labile, _saccade);
	yb.insert(output);
	//printf("%f\tSaccadeTimer: Threshold reached for new saccade[id=%d] \n", _time, saccade->id);
}

void SaccadeTimer::gc_output(Bag<IO_Type>& g)
{
	Bag<IO_Type>::iterator i;
	for (i = g.begin(); i != g.end(); i++)
	{
		delete (*i).value;
	}
}

SaccadeTimer::~SaccadeTimer()
{
}
