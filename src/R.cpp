#include "stdlib.h"
#include "CRISP.h"
#include "Data.h"

#include "Rcpp.h"

using namespace std;
using namespace Rcpp;

// [[Rcpp::export("crisp")]]
DataFrame crispR(
		int n,
		double tsac=250, double N=11,
		double m_lab=180, double sd_lab=45,
		double m_nlab=40, double sd_nlab=10,
		double m_ex=40, double sd_ex=13)
{
	std::vector<double> id(n);
	std::vector<double> cancelations(n);
	std::vector<double> mergers(n);
	std::vector<double> timer_start(n);
	std::vector<double> timer_stop(n);
	std::vector<double> labile_first(n);
	std::vector<double> labile_start(n);
	std::vector<double> labile(n);
	std::vector<double> labile_full(n);
	std::vector<double> labile_stop(n);
	std::vector<double> nonlabile_start(n);
	std::vector<double> nonlabile(n);
	std::vector<double> nonlabile_stop(n);
	std::vector<double> exec_start(n);
	std::vector<double> exec(n);
	std::vector<double> exec_full(n);
	std::vector<double> exec_stop(n);
	std::vector<double> fixation_start(n);
	std::vector<double> fixation(n);
	std::vector<double> fixation_stop(n);
	CRISP_t c = crisp(n, tsac, N, m_lab, sd_lab, m_nlab, sd_nlab, m_ex, sd_ex);
	vector<Saccade*> data = *c.saccades;
	vector<Saccade*>::iterator d = data.begin();
	for (int i=0 ;d != data.end(); d++,i++) {
		id[i] = (*d)->id;
		cancelations[i] = (*d)->cancelations;
		mergers[i] = (*d)->mergers;
		timer_start[i] = (*d)->timer_start;
		timer_stop[i] = (*d)->timer_stop;
		labile_first[i] = (*d)->labile_first;
		labile_start[i] = (*d)->labile_start;
		labile[i] = (*d)->labile_stop - (*d)->labile_start;
		labile_full[i] = (*d)->labile_stop - (*d)->labile_first;
		labile_stop[i] = (*d)->labile_stop;
		nonlabile_start[i] = (*d)->nonlabile_start;
		nonlabile[i] = (*d)->nonlabile_stop - (*d)->nonlabile_start;
		nonlabile_stop[i] = (*d)->nonlabile_stop;
		exec_start[i] = (*d)->exec_start;
		exec[i] = (*d)->exec_stop - (*d)->exec_start;
		exec_full[i] = (*d)->exec_stop - (*d)->exec_first;
		exec_stop[i] = (*d)->exec_stop;
		fixation_start[i] = (*d)->fixation_start;
		fixation[i] = (*d)->fixation_stop - (*d)->fixation_start;
		fixation_stop[i] = (*d)->fixation_stop;
	}
	DataFrame out = DataFrame::create(
			Named("id")=id,
			Named("cancelations")=cancelations,
			Named("mergers")=mergers,
			Named("timer_start")=timer_start,
			Named("timer_stop")=timer_stop,
			Named("labile_first")=labile_first,
			Named("labile_start")=labile_start,
			Named("labile")=labile,
			Named("labile_full")=labile_full,
			Named("labile_stop")=labile_stop,
			Named("nonlabile_start")=nonlabile_start,
			Named("nonlabile")=nonlabile,
			Named("nonlabile_stop")=nonlabile_stop,
			Named("exec_start")=exec_start,
			Named("exec")=exec,
			Named("exec_full")=exec_full,
			Named("exec_stop")=exec_stop,
			Named("fixation_start")=fixation_start,
			Named("fixation")=fixation,
			Named("fixation_stop")=fixation_stop
			);
	//out.attr("jams") = c.jams;
	return out;
}
