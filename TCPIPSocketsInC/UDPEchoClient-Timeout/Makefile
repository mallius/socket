include ../Make.defines

PROGS =	UDPEchoClient-Timeout 


all:	${PROGS}

UDPEchoClient-Timeout:	UDPEchoClient-Timeout.o 
		${CC} ${CFLAGS} -o $@ UDPEchoClient-Timeout.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

