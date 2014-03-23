#include "SaccadeMotorProgram.h"
#include "ansi.h"
using namespace std;
using namespace adevs;

const int SaccadeMotorProgram::nonlabile = 0;
const int SaccadeMotorProgram::execute = 1;

SaccadeMotorProgram::SaccadeMotorProgram(std::mt19937& twister):Atomic<IO_Type>(),
		_mean(40),
		_stdev(10),
		_time(0.0),
		_threshold(DBL_MAX),
		_saccade(NULL)
{
	_twister = twister;
}

double SaccadeMotorProgram::ta()
{
	return _threshold;
}

void SaccadeMotorProgram::delta_int()
{
}

void SaccadeMotorProgram::delta_ext(double e, const Bag<IO_Type>& xb)
{
	std::gamma_distribution<double> dist(((_mean*_mean)/(_stdev*_stdev)),(_stdev*_stdev)/_mean);

	_time += e;
	if (_saccade) {
		printf(YELLOW "%f\t    SaccadeMotorProgram: Program saccade[id=%d] is getting canceled!\n" RESET, _time, _saccade->id);
	}
	_saccade = new Saccade(*((*xb.begin()).value));
	_threshold = dist(_twister);

	//printf("%f\t    SaccadeMotorProgram: Starting non-labile programming for saccade[id=%d]\n", _time, _saccade->id);

	//printf("%f\t    SaccadeMotorProgram: Next event at %f\n", _time, _time+_threshold);
}

void SaccadeMotorProgram::delta_conf(const Bag<IO_Type>& xb)
{
	delta_int();
	delta_ext(0.0,xb);
}

void SaccadeMotorProgram::output_func(Bag<IO_Type>& yb)
{
	IO_Type output(execute, _saccade);
	yb.insert(output);
	_time += _threshold;
	_threshold = DBL_MAX;
	//printf("%f\t    SaccadeMotorProgram: Non-labile programming complete\n", _time);
}

void SaccadeMotorProgram::gc_output(Bag<IO_Type>& g)
{
	Bag<IO_Type>::iterator i;
	for (i = g.begin(); i != g.end(); i++)
		delete (*i).value;
	_saccade = NULL;
}

SaccadeMotorProgram::~SaccadeMotorProgram()
{
}
