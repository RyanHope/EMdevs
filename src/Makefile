OBJECTS			= SaccadeTimer.o \
				  SaccadeTargetSelect.o \
				  SaccadeMotorProgram.o \
				  SaccadeExec.o \
				  CRISP.o \
				  R.o \
				  RcppExports.o

all: lib

lib:
	R CMD SHLIB ${OBJECTS} -o EMdevs.so
	
.PHONY: clean
clean:
	rm -rf *.o *.so