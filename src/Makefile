CXXFLAGS	= -march=native -O3 -pipe -std=c++11 -Wall -g -pedantic -fopenmp
INCLUDE		= -Iinclude

CRISP_OBJS	= SaccadeTimer.o SaccadeTargetPlanner.o SaccadeMovementProgrammer.o SaccadeExec.o

.SUFFIXES: .cpp
.cpp.o:
	${CXX} -c ${CXXFLAGS} ${INCLUDE} $<
	
all: crisp

crisp: ${CRISP_OBJS} main.o
	${CXX} ${CXXFLAGS} $^ -o $@
	
clean:
	rm -rf *.o crisp