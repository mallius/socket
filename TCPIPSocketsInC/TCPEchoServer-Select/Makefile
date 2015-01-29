include ../Make.defines

PROGS =	TCPEchoServer-Select 


all:	${PROGS}

TCPEchoServer-Select:	TCPEchoServer-Select.o 
		${CC} ${CFLAGS} -o $@ TCPEchoServer-Select.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

