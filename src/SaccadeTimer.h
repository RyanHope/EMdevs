
#ifndef __SaccadeTimer_h_
#define __SaccadeTimer_h_
#include <random>
#include <cmath>
#include "adevs.h"
#include "Saccade.h"

class SaccadeTimer: public adevs::Atomic<IO_Type>
{
	public:
		SaccadeTimer(std::mt19937& twister, std::uniform_real_distribution<>& unif_dist, double mean_duration=250, int states=11);
		void delta_int();
		void delta_ext(double e, const adevs::Bag<IO_Type>& xb);
		void delta_conf(const adevs::Bag<IO_Type>& xb);
		void output_func(adevs::Bag<IO_Type>& yb);
		double ta();
		void gc_output(adevs::Bag<IO_Type>& g);
		~SaccadeTimer();
		static const int labile;
	private:
		std::mt19937 _twister;
		std::uniform_real_distribution<> _unif_dist;

		double _threshold;
		double _time;

		double _mean_duration;
		int _states;

		int _n;
};

#endif
