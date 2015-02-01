include ../Make.defines

PROGS =	TCPEchoServer4 


all:	${PROGS}

TCPEchoServer4:	TCPEchoServer4.o 
		${CC} ${CFLAGS} -o $@ TCPEchoServer4.o ${LIBS}
GetAddrInfo:	GetAddrInfo.o 
		${CC} ${CFLAGS} -o $@ GetAddrInfo.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

