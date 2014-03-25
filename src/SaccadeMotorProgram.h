
#ifndef __SaccadeMotorProgram_h_
#define __SaccadeMotorProgram_h_
#include "adevs.h"
#include "Saccade.h"
#include <list>

class SaccadeMotorProgram: public adevs::Atomic<IO_Type>
{
	public:
		SaccadeMotorProgram(double mean=40, double stdev=10);
		void delta_int();
		void delta_ext(double e, const adevs::Bag<IO_Type>& xb);
		void delta_conf(const adevs::Bag<IO_Type>& xb);
		void output_func(adevs::Bag<IO_Type>& yb);
		double ta();
		void gc_output(adevs::Bag<IO_Type>& g);
		~SaccadeMotorProgram();
		static const int nonlabile;
		static const int execute;
		int jams;
	private:
		double _mean;
		double _stdev;
		double _time;
		double _threshold;
		std::list<Saccade*> _saccades;
};

#endif
