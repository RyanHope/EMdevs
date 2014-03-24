#include "SaccadeTimer.h"
using namespace std;
using namespace adevs;

const int SaccadeTimer::labile = 1;

SaccadeTimer::SaccadeTimer(std::mt19937& twister, std::uniform_real_distribution<>& unif_dist):Atomic<IO_Type>(),
		_threshold(0.0),
		_time(0.0),
		_mean_duration(250),
		_states(11),
		_n(0)
{
	_twister = twister;
	_unif_dist = unif_dist;
	delta_int();
}

double SaccadeTimer::ta()
{
	return _threshold;
}

void SaccadeTimer::delta_int()
{
	_threshold = 0;
	for(int i = 0; i < _states; ++i) _threshold -= (_mean_duration/_states)*std::log(1-_unif_dist(_twister));
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
	Saccade *saccade = new Saccade(++_n);
	IO_Type output(labile, saccade);
	yb.insert(output);
	_time += _threshold;
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
