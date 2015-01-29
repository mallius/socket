include ../Make.defines

PROGS =	TCPEchoClient4 


all:	${PROGS}

TCPEchoClient4:	TCPEchoClient4.o 
		${CC} ${CFLAGS} -o $@ TCPEchoClient4.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

