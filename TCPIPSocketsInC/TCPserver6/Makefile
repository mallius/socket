include ../Make.defines

PROGS =	TCPEchoServer6 


all:	${PROGS}

TCPEchoServer6:	TCPEchoServer6.o 
		${CC} ${CFLAGS} -o $@ TCPEchoServer6.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

