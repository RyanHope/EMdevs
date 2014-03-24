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
	std::vector<double> nonlabile(n);
	std::vector<double> exec(n);
	std::vector<double> fixation(n);
	list<CRISP_d*> data = crisp(n, tsac, N, m_lab, sd_lab, m_nlab, sd_nlab, m_ex, sd_ex);
	list<CRISP_d*>::iterator d = data.begin();
	for (int i=0 ;d != data.end(); d++,i++) {
		id[i] = (*d)->id;
		cancelations[i] = (*d)->cancelations;
		labile[i] = (*d)->labile;
		nonlabile[i] = (*d)->nonlabile;
		exec[i] = (*d)->exec;
		fixation[i] = (*d)->fixation;
	}
	return DataFrame::create(
			Named("id")=id,
			Named("cancelations")=cancelations,
			Named("labile")=labile,
			Named("nonlabile")=labile,
			Named("exec")=exec,
			Named("fixation")=fixation
			);
}
