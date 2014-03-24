#include "Rcpp.h"

#include "Saccade.h"
#include "SaccadeTimer.h"
#include "SaccadeTargetSelect.h"
#include "SaccadeMotorProgram.h"
#include "SaccadeExec.h"

#include "CRISP.h"

using namespace std;
using namespace adevs;

class StateListener: public EventListener< PortValue<Saccade*> >
{
	public:
		StateListener():data(),count(0){}
		vector<Saccade*> data;
		int count;
		void outputEvent(Event< PortValue<Saccade*> > x, double t){
			if (dynamic_cast<SaccadeExec*>(x.model) != NULL) {
				data.push_back(new Saccade(*x.value.value));
				count++;
			}
		}
};


vector<Saccade*> crisp(
		int n,
		double tsac, double N,
		double m_lab, double sd_lab,
		double m_nlab, double sd_nlab,
		double m_ex, double sd_ex)
{
	Rcpp::RNGScope scope;
	Digraph<Saccade*> crisp;
	SaccadeTimer* timer = new SaccadeTimer(tsac, N);
	SaccadeTargetSelect* target = new SaccadeTargetSelect(m_lab, sd_lab);
	SaccadeMotorProgram* motor = new SaccadeMotorProgram(m_nlab, sd_nlab);
	SaccadeExec* exec = new SaccadeExec(m_ex, sd_ex);
	crisp.add(timer);
	crisp.add(target);
	crisp.add(motor);
	crisp.add(exec);
	crisp.couple(timer, timer->labile, target, target->labile);
	crisp.couple(target, target->nonlabile, motor, motor->nonlabile);
	crisp.couple(motor, motor->execute, exec, exec->execute);
	Simulator< PortValue<Saccade*> > sim(&crisp);
	StateListener* s = new StateListener();
	sim.addEventListener(s);
	while (s->count < n && sim.nextEventTime() < DBL_MAX)
	{
		sim.execNextEvent();
	}
	return s->data;
}
