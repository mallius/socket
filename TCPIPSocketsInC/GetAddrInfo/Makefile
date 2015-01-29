include ../Make.defines

PROGS =	GetAddrInfo


all:	${PROGS}

GetAddrInfo:	GetAddrInfo.o 
		${CC} ${CFLAGS} -o $@ GetAddrInfo.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

