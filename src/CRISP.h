#ifndef CRISP_h_
#define CRISP_h_

#include "Data.h"
#include <list>

std::list<CRISP_d*> crisp(
		int n,
		double tsac, double N1,
		double m_lab, double sd_lab,
        double m_nlab, double sd_nlab,
        double m_ex, double sd_ex);

#endif
