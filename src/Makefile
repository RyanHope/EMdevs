CXXFLAGS		= -march=native -O3 -pipe -std=c++11 -Wall -g -pedantic -fopenmp -fPIC
R_INCLUDE		= -I$(shell R RHOME)/include
RCPP_INCLUDE	= $(shell Rscript -e 'Rcpp:::CxxFlags()')
INCLUDE			= -Iinclude ${R_INCLUDE} ${RCPP_INCLUDE}
LDFLAGS			= -lR -L$(shell R RHOME)/lib

CRISP_OBJS		= SaccadeTimer.o SaccadeTargetSelect.o SaccadeMotorProgram.o SaccadeExec.o
CRISP_CORE		= ${CRISP_OBJS} CRISP.o
CRISP_BIN		= ${CRISP_CORE} main.o
CRISP_R			= ${CRISP_CORE} R.o RcppExports.o

lib: EMdevs.so

all: crisp EMdevs.so

.SUFFIXES: .cpp
.cpp.o:
	${CXX} -c ${CXXFLAGS} ${INCLUDE} $<
	
crisp: ${CRISP_BIN}
	${CXX} ${LDFLAGS} $^ -o $@
	
EMdevs.so: ${CRISP_R}
	${CXX} ${LDFLAGS} -shared -Wl,-O1 -Wl,--sort-common -Wl,--as-needed $^ -o EMdevs.so
	
.PHONY: clean
clean:
	rm -rf *.o *.so crisp