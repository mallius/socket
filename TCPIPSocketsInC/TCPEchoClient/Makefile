include ../Make.defines

PROGS =	TCPEchoClient 


all:	${PROGS}

TCPEchoClient:	TCPEchoClient.o 
		${CC} ${CFLAGS} -o $@ TCPEchoClient.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

