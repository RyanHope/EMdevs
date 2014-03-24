#ifndef CRISP_h_
#define CRISP_h_

#include "Saccade.h"
#include <vector>

std::vector<Saccade*> crisp(
		int n,
		double tsac, double N1,
		double m_lab, double sd_lab,
        double m_nlab, double sd_nlab,
        double m_ex, double sd_ex);

#endif
