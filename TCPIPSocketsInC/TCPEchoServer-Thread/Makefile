include ../Make.defines

PROGS =	TCPEchoServer-Thread 


all:	${PROGS}

TCPEchoServer-Thread:	TCPEchoServer-Thread.o 
		${CC} ${CFLAGS} -o $@ TCPEchoServer-Thread.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

