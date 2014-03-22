OMP = -fopenmp
CFLAGS += ${OMP} -fPIC -Wall -I../include -I./
OPTFLAG = -O3

ADEVS_OBJS = \
	rv.o \
	poly.o \
	time.o

.SUFFIXES: .cpp .c
.cpp.o:
	${CXX} ${CFLAGS} ${OPTFLAG} -o $@ -c $<
.c.o:
	${CC} ${CFLAGS} ${OPTFLAG} -o $@ -c $<

adevs: ${ADEVS_OBJS} 
	ar -r libadevs.a ${ADEVS_OBJS}
	${CXX} -shared -Wl,-soname,libadevs.so.2 -o libadevs.so.2.8 ${ADEVS_OBJS}

install:
	mkdir -p "${DESTDIR}"
	install -m 755 -p libadevs.so.2.8 "${DESTDIR}"
	ln -f -s libadevs.so.2.8 "${DESTDIR}/libadevs.so.2"
	ln -f -s libadevs.so.2.8 "${DESTDIR}/libadevs.so"

clean:
	rm -f *.o core *.a *.so libadevs.so.*
