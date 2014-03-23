#include <random>
#include <chrono>

#include "Saccade.h"
#include "SaccadeTimer.h"
#include "SaccadeTargetPlanner.h"
#include "SaccadeMovementProgrammer.h"
#include "SaccadeExec.h"

using namespace std;
using namespace adevs;

class StateListener: public EventListener< PortValue<Saccade*> >
{
	public:
		StateListener(SaccadeTimer* c1, SaccadeTargetPlanner* c2, SaccadeMovementProgrammer* c3):c1(c1),c2(c2),c3(c3){}
		void outputEvent(Event< PortValue<Saccade*> > x, double t){
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			/*if (dynamic_cast<SaccadeTimer*>(x.model) != NULL)
				cout << "\x1b[34;1m" << "~" << t << "~\t\tSaccadeTimer: NEW SACCADE" << "\x1b[0m" << endl;
			else if (dynamic_cast<SaccadeTargetPlanner*>(x.model) != NULL)
				cout << "\x1b[34;1m" << "~" << t << "~\t\t   SaccadeTargetPlanner: LABILE COMPLETE" << "\x1b[0m" << endl;
			else if (dynamic_cast<SaccadeMovementProgrammer*>(x.model) != NULL)
				cout << "\x1b[34;1m" << "~" << t << "~\t\t     SaccadeMovementProgrammer: NON-LABILE COMPLETE" << "\x1b[0m" << endl;*/
		}
	private:
		SaccadeTimer* c1; SaccadeTargetPlanner* c2; SaccadeMovementProgrammer* c3;
};

int main(int argc, char** argv)
{
	std::mt19937 twister(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<> unif_dist(0, 1);

	Digraph<Saccade*> crisp;
	SaccadeTimer* timer = new SaccadeTimer(twister, unif_dist);
	SaccadeTargetPlanner* target_planner = new SaccadeTargetPlanner(twister);
	SaccadeMovementProgrammer* movement_programmer = new SaccadeMovementProgrammer(twister);
	SaccadeExec* exec = new SaccadeExec(twister);
	crisp.add(timer);
	crisp.add(target_planner);
	crisp.add(movement_programmer);
	crisp.add(exec);
	crisp.couple(timer, timer->labile, target_planner, target_planner->labile);
	crisp.couple(target_planner, target_planner->nonlabile, movement_programmer, movement_programmer->nonlabile);
	crisp.couple(movement_programmer, movement_programmer->execute, exec, exec->execute);
	Simulator< PortValue<Saccade*> > sim(&crisp);
	sim.addEventListener(new StateListener(timer,target_planner,movement_programmer));
	while (sim.nextEventTime() < DBL_MAX)
	{
		sim.execNextEvent();
	}
	return 0;
}
