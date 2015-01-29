#include "../include/Practical.h"


void ProcessMain(int servSock);

int main(int argc, char *argv[])
{
	if(argc != 3) 
		DieWithUserMessage("Parameters(s)", "<Server Port/Service><Process Count>");

	char *service = argv[1];
	unsigned int processLimit = atoi(argv[2]);
	int servSock = SetupTCPServerSocket(service);
	if(servSock < 0)
		DieWithUserMessage("SetupTCPServerSocket() failed", "unable to establish");

	/* Fork limit-1 child processes */
	int processCt = 0;


	for(processCt = 0; processCt < processLimit -1; processCt++)
	{
		pid_t processID = fork();

		if(processID < 0)
			DieWithSystemMessage("fork() failed");
		else if(processID == 0)
		{
			ProcessMain(servSock);
		}
		ProcessMain(servSock);
	}
}

void ProcessMain(int servSock)
{
	for(;;)
	{
		int clntSock = AcceptTCPConnection(servSock);
		printf("with child process: %d\n", getpid());
		HandleTCPClient(clntSock);
	}
}
