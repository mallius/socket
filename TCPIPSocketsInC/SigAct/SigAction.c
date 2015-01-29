#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "../include/Practical.h"

void InterruptSignalHandler(int signalType);

int main(int argc, char *argv[])
{
	struct sigaction handler;

	handler.sa_handler = InterruptSignalHandler;
	if(sigfillset(&handler.sa_mask) < 0)
		DieWithSystemMessage("sigfillset() failed");
	handler.sa_flags = 0;

	if(sigaction(SIGINT, &handler, 0) < 0)
		DieWithSystemMessage("sigaction() failed for SIGINT");

	for(;;)
		pause();

	exit(0);
}

void InterruptSignalHandler(int signalType)
{
	puts("Interrupt Received. Exiting program.");
	exit(1);
}
