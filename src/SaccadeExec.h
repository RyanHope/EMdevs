
#ifndef __SaccadeExec_h_
#define __SaccadeExec_h_
#include "adevs.h"
#include "Saccade.h"

class SaccadeExec: public adevs::Atomic<IO_Type>
{
	public:
		SaccadeExec(std::mt19937& twister);
		void delta_int();
		void delta_ext(double e, const adevs::Bag<IO_Type>& xb);
		void delta_conf(const adevs::Bag<IO_Type>& xb);
		void output_func(adevs::Bag<IO_Type>& yb);
		double ta();
		void gc_output(adevs::Bag<IO_Type>& g);
		~SaccadeExec();
		static const int execute;
		static const int fixation;
	private:
		double _mean;
		double _stdev;
		std::mt19937 _twister;
		double _time;
		double _threshold;
		Saccade* _saccade;
};

#endif
