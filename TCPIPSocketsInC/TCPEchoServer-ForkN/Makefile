include ../Make.defines

PROGS =	TCPEchoServer-ForkN 


all:	${PROGS}

TCPEchoServer-ForkN:	TCPEchoServer-ForkN.o 
		${CC} ${CFLAGS} -o $@ TCPEchoServer-ForkN.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

