#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../include/Practical.h"

#define BUFSIZE 1024

static const int MAXPENDING = 5;


int main(int argc, char *argv[])
{
	if(argc != 2) 
		DieWithUserMessage("Parameters(s)", "<Server Port>");

	char *service = argv[1];
	int servSock = SetupTCPServerSocket(service);
	if(servSock < 0)
		DieWithUserMessage("SetupTCPServerSocket() failed", "unable to establish");
	unsigned int childProcCount = 0;	


	for(;;)
	{
		int clntSock = AcceptTCPConnection(servSock);
		pid_t processID = fork();
		if(processID < 0)
			DieWithSystemMessage("fork() failed");
		else if(processID == 0)
		{
			close(servSock);
			HandleTCPClient(clntSock);
			exit(0);
		}
		printf("with child process: %d\n", processID);
		close(clntSock);
		childProcCount++;
		
		while(childProcCount)
		{
			processID = waitpid((pid_t)-1, NULL, WNOHANG);
			if(processID < 0)
				DieWithSystemMessage("waitpid() failed");
			else if(processID == 0)
				break;
			else
				childProcCount--;
		}

	}
}
