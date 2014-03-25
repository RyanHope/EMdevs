#ifndef CRISP_h_
#define CRISP_h_

#include "Saccade.h"
#include <vector>

typedef struct
{
	std::vector<Saccade*>* saccades;
	int jams;
} CRISP_t;

CRISP_t crisp(
		int n,
		double tsac, double N1,
		double m_lab, double sd_lab,
        double m_nlab, double sd_nlab,
        double m_ex, double sd_ex);

#endif
