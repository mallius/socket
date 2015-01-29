include ../Make.defines

PROGS =	UDPEchoServer 


all:	${PROGS}

UDPEchoServer:	UDPEchoServer.o 
		${CC} ${CFLAGS} -o $@ UDPEchoServer.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

