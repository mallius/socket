include ../Make.defines

PROGS =	SigAction 


all:	${PROGS}

SigAction:	SigAction.o 
		${CC} ${CFLAGS} -o $@ SigAction.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

