CXXFLAGS		:= -march=native -O3 -pipe -std=c++11 -Wall -g -pedantic -fopenmp
R_INCLUDE		:= -I`R RHOME`/include
RCPP_INCLUDE	:= `Rscript -e 'Rcpp:::CxxFlags()'`
INCLUDE			:= -Iinclude ${R_INCLUDE} ${RCPP_INCLUDE}
LDFLAGS			:= -lR -L`R RHOME`/lib

CRISP_OBJS	:= SaccadeTimer.o SaccadeTargetSelect.o SaccadeMotorProgram.o SaccadeExec.o CRISP.o

.SUFFIXES: .cpp
.cpp.o:
	${CXX} -c ${CXXFLAGS} ${INCLUDE} $<
	
all: crisp

crisp: ${CRISP_OBJS} main.o
	${CXX} ${LDFLAGS} $^ -o $@
	
clean:
	rm -rf *.o crisp