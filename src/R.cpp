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
	std::vector<double> labile(n);
	std::vector<double> labile_full(n);
	std::vector<double> nonlabile(n);
	std::vector<double> exec(n);
	std::vector<double> fixation_start(n);
	std::vector<double> fixation_stop(n);
	vector<Saccade*> data = crisp(n, tsac, N, m_lab, sd_lab, m_nlab, sd_nlab, m_ex, sd_ex);
	vector<Saccade*>::iterator d = data.begin();
	for (int i=0 ;d != data.end(); d++,i++) {
		id[i] = (*d)->id;
		cancelations[i] = (*d)->cancelations;
		labile[i] = (*d)->labile_stop - (*d)->labile_start;
		labile_full[i] = (*d)->labile_stop - (*d)->labile_first;
		nonlabile[i] = (*d)->nonlabile_stop - (*d)->nonlabile_start;
		exec[i] = (*d)->exec_stop - (*d)->exec_start;
		fixation_start[i] = (*d)->fixation_start;
		fixation_stop[i] = (*d)->fixation_stop;
	}
	return DataFrame::create(
			Named("id")=id,
			Named("cancelations")=cancelations,
			Named("labile")=labile,
			Named("labile_full")=labile_full,
			Named("nonlabile")=nonlabile,
			Named("exec")=exec,
			Named("fixation_start")=fixation_start,
			Named("fixation_stop")=fixation_stop
			);
}
