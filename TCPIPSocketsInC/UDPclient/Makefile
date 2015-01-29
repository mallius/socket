include ../Make.defines

PROGS =	UDPEchoClient 


all:	${PROGS}

UDPEchoClient:	UDPEchoClient.o 
		${CC} ${CFLAGS} -o $@ UDPEchoClient.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

