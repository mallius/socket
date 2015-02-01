include ../Make.defines

PROGS =	TCPEchoServer 


all:	${PROGS}

TCPEchoServer:	TCPEchoServer.o 
		${CC} ${CFLAGS} -o $@ TCPEchoServer.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

