#include <random>
#include <chrono>

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
		StateListener(int n):fixations_start(0),fixations_end(0),data(){}
		int fixations_start;
		int fixations_end;
		list<CRISP_d*> data;
		double time = 0;
		void outputEvent(Event< PortValue<Saccade*> > x, double t){
			//cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			if (dynamic_cast<SaccadeMotorProgram*>(x.model) != NULL) {
				if (fixations_start>0) {
					++fixations_end;
					CRISP_d* d = data.back();
					d->fixation = t - time;
					//printf("~~@@~~~~ | Fixation %d End | ~~~~@@~~\n", fixations_end);
				}
				//printf("~~@@~~~~ | Saccade Start | ~~~~@@~~\n");
			} else if (dynamic_cast<SaccadeExec*>(x.model) != NULL) {
				++fixations_start;
				time = t;
				Saccade* s = (Saccade*)x.value.value;
				data.push_back(new CRISP_d(
						s->id,
						s->cancelations,
						(s->labile_stop - s->labile_start),
						(s->nonlabile_stop - s->nonlabile_start),
						(s->exec_stop - s->exec_start),
						0.0
						));
				//printf("~~@@~~~~ | Saccade End | ~~~~@@~~\n");
				//printf("~~@@~~~~ | Fixation %d Start | ~~~~@@~~\n", fixations_start);
			}
		}
};


list<CRISP_d*> crisp(
		int n,
		double tsac, double N,
		double m_lab, double sd_lab,
		double m_nlab, double sd_nlab,
		double m_ex, double sd_ex)
{
	std::mt19937 twister(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<> unif_dist(0, 1);

	Digraph<Saccade*> crisp;
	SaccadeTimer* timer = new SaccadeTimer(twister, unif_dist);
	SaccadeTargetSelect* target = new SaccadeTargetSelect(twister);
	SaccadeMotorProgram* motor = new SaccadeMotorProgram(twister);
	SaccadeExec* exec = new SaccadeExec(twister);
	crisp.add(timer);
	crisp.add(target);
	crisp.add(motor);
	crisp.add(exec);
	crisp.couple(timer, timer->labile, target, target->labile);
	crisp.couple(target, target->nonlabile, motor, motor->nonlabile);
	crisp.couple(motor, motor->execute, exec, exec->execute);
	Simulator< PortValue<Saccade*> > sim(&crisp);
	StateListener* s = new StateListener(N);
	sim.addEventListener(s);
	while (s->fixations_end < n && sim.nextEventTime() < DBL_MAX)
	{
		sim.execNextEvent();
	}
	return s->data;
}
