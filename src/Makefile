CXXFLAGS		= -march=native -O3 -pipe -std=c++11 -Wall -g -pedantic -fopenmp
R_INCLUDE		= -I`R RHOME`/include
RCPP_INCLUDE	= `Rscript -e 'Rcpp:::CxxFlags()'`
INCLUDE			= -Iinclude ${R_INCLUDE} ${RCPP_INCLUDE}
LDFLAGS			= -lR -L`R RHOME`/lib

CRISP_OBJS		= SaccadeTimer.o SaccadeTargetSelect.o SaccadeMotorProgram.o SaccadeExec.o
CRISP_CORE		= ${CRISP_OBJS} CRISP.o
CRISP_BIN		= ${CRISP_CORE} main.o 

all: crisp

.SUFFIXES: .cpp
.cpp.o:
	${CXX} -c ${CXXFLAGS} ${INCLUDE} $<
	
crisp: ${CRISP_BIN}
	${CXX} ${LDFLAGS} $^ -o $@
	
.PHONY: clean
clean:
	rm -rf *.o crisp