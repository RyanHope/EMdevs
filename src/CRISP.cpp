#include <random>
#include <chrono>

#include "Saccade.h"
#include "SaccadeTimer.h"
#include "SaccadeTargetSelect.h"
#include "SaccadeMotorProgram.h"
#include "SaccadeExec.h"

#include "CRISP.h"
#include <Rcpp.h>

using namespace std;
using namespace adevs;

class StateListener: public EventListener< PortValue<Saccade*> >
{
	public:
		StateListener(int n):fixations_start(0),fixations_end(0),saccades(){}
		int fixations_start;
		int fixations_end;
		list<Saccade*> saccades;
		double time = 0;
		void outputEvent(Event< PortValue<Saccade*> > x, double t){
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			if (dynamic_cast<SaccadeMotorProgram*>(x.model) != NULL) {
				if (fixations_start>0) {
					++fixations_end;
					Saccade* s = saccades.back();
					s->fixation_duration = t - time;
					printf("~~@@~~~~ | Fixation %d End | ~~~~@@~~\n", fixations_end);
				}
				printf("~~@@~~~~ | Saccade Start | ~~~~@@~~\n");
			} else if (dynamic_cast<SaccadeExec*>(x.model) != NULL) {
				++fixations_start;
				time = t;
				saccades.push_back(new Saccade(*(Saccade*)x.value.value));
				printf("~~@@~~~~ | Saccade End | ~~~~@@~~\n");
				printf("~~@@~~~~ | Fixation %d Start | ~~~~@@~~\n", fixations_start);
			}
		}
};


int crisp(
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
	list<Saccade*>::iterator saccades = s->saccades.begin();
	for ( ;saccades != s->saccades.end(); saccades++) {
		cout << (*saccades)->id << "\t"
				<< (*saccades)->cancelations << "\t"
				<< (*saccades)->labile_stop - (*saccades)->labile_start << "\t"
				<< (*saccades)->nonlabile_stop - (*saccades)->nonlabile_start << "\t"
				<< (*saccades)->exec_stop - (*saccades)->exec_start << "\t"
				<< (*saccades)->fixation_duration
				<< endl;
	}
	std::vector<double> durations(n);
	std::vector<double> cancelations(n);
	std::vector<double> labile(n);
	/*return Rcpp::DataFrame::create(
			Rcpp::Named("duration")=durations,
			Rcpp::Named("cancelations")=cancelations,
			Rcpp::Named("labile")=labile
			);*/
	return 0;
}
