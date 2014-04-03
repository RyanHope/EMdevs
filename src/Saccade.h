
#ifndef __Saccade_h_
#define __Saccade_h_
#include "adevs.h"

struct Saccade
{
	int id;
	int cancelations;
	int mergers;
	double timer_start;
	double timer_stop;
	double labile_first;
	double labile_start;
	double labile_stop;
	double nonlabile_t;
	double nonlabile_start;
	double nonlabile_stop;
	double exec_first;
	double exec_start;
	double exec_stop;
	double fixation_start;
	double fixation_stop;
	Saccade(int i, double start):
		cancelations(0),
		mergers(0),
		timer_start(0.0),
		timer_stop(0.0),
		labile_first(0.0),
		labile_start(0.0),
		labile_stop(0.0),
		nonlabile_t(0.0),
		nonlabile_start(0.0),
		nonlabile_stop(0.0),
		exec_first(0.0),
		exec_start(0.0),
		exec_stop(0.0),
		fixation_start(0.0),
		fixation_stop(0.0)
	{
		id = i;
		timer_start = start;
	}
};

typedef adevs::PortValue<Saccade*> IO_Type;

#endif
