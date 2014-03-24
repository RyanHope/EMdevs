#include "stdlib.h"
#include "CRISP.h"
#include "Data.h"

using namespace std;

int main(int argc, char** argv)
{
	int N = 10;
	if (argc == 2) {
		int n = atoi(argv[1]);
		if (n > 0) N = n;
		else return(-1);
	}
	list<CRISP_d*> data = crisp(N, 250, 11, 180, 45, 40, 10, 40, 13);
	/*
	list<CRISP_d*>::iterator d = data.begin();
	for ( ;d != data.end(); d++) {
		cout << (*d)->id << "\t"
				<< (*d)->cancelations << "\t"
				<< (*d)->labile << "\t"
				<< (*d)->nonlabile << "\t"
				<< (*d)->exec << "\t"
				<< (*d)->fixation
				<< endl;
	}
	*/
	return 0;
}
