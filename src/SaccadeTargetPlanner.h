
#ifndef __SaccadeTargetPlanner_h_
#define __SaccadeTargetPlanner_h_
#include "adevs.h"
#include "Saccade.h"

class SaccadeTargetPlanner: public adevs::Atomic<IO_Type>
{
	public:
		SaccadeTargetPlanner(std::mt19937& twister);
		void delta_int();
		void delta_ext(double e, const adevs::Bag<IO_Type>& xb);
		void delta_conf(const adevs::Bag<IO_Type>& xb);
		void output_func(adevs::Bag<IO_Type>& yb);
		double ta();
		void gc_output(adevs::Bag<IO_Type>& g);
		~SaccadeTargetPlanner();
		static const int labile;
		static const int nonlabile;
	private:
		double _mean;
		double _stdev;
		std::mt19937 _twister;
		double _time;
		double _threshold;
		Saccade* _saccade;
};

#endif
