include ../Make.defines

PROGS =	TCPEchoServer-Fork 


all:	${PROGS}

TCPEchoServer-Fork:	TCPEchoServer-Fork.o 
		${CC} ${CFLAGS} -o $@ TCPEchoServer-Fork.o ${LIBS}
GetAddrInfo:	GetAddrInfo.o 
		${CC} ${CFLAGS} -o $@ GetAddrInfo.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

