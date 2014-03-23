
#ifndef __Saccade_h_
#define __Saccade_h_
#include "adevs.h"

struct Saccade
{
	int id;
	int cancelations;
	double timer;
	Saccade(int i, int c)
	{
		id = i;
		cancelations = c;
	}
};

typedef adevs::PortValue<Saccade*> IO_Type;

#endif
