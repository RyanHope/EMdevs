#include "stdlib.h"
#include "CRISP.h"

using namespace std;

int main(int argc, char** argv)
{
	int N = 10;
	if (argc == 2) {
		int n = atoi(argv[1]);
		if (n > 0) N = n;
		else return(-1);
	}
	crisp(N, 250, 11, 180, 45, 40, 10, 40, 13);
	return 0;
}
