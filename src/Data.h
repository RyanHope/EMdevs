
#ifndef __Data_h_
#define __Data_h_

struct CRISP_d
{
	int id;
	int cancelations;
	double labile;
	double nonlabile;
	double exec;
	double fixation;
	CRISP_d(int i,
			int c,
			double l,
			double n,
			double e,
			double f) {
		id = i;
		cancelations = c;
		labile = l;
		nonlabile = n;
		exec = e;
		fixation = f;
	}
};

#endif
