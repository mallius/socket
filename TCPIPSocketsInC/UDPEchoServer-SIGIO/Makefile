include ../Make.defines

PROGS =	UDPEchoServer-SIGIO 


all:	${PROGS}

UDPEchoServer-SIGIO:	UDPEchoServer-SIGIO.o 
		${CC} ${CFLAGS} -o $@ UDPEchoServer-SIGIO.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}

