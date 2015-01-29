#include "../include/Practical.h"

#define BUFSIZE 1024

static const int MAXPENDING = 5;
void *ThreadMain(void *arg);
struct ThreadArgs{
	int clntSock;
};

int main(int argc, char *argv[])
{
	if(argc != 2) 
		DieWithUserMessage("Parameters(s)", "<Server Port>");

	char *service = argv[1];
	int servSock = SetupTCPServerSocket(service);
	if(servSock < 0)
		DieWithUserMessage("SetupTCPServerSocket() failed", "unable to establish");


	for(;;)
	{
		int clntSock = AcceptTCPConnection(servSock);

		struct ThreadArgs *threadArgs = (struct ThreadArgs *)malloc(sizeof(struct ThreadArgs));
		if(threadArgs == NULL)
			DieWithSystemMessage("malloc() failed");
		threadArgs->clntSock = clntSock;

		pthread_t threadID;
		int returnValue = pthread_create(&threadID, NULL, ThreadMain, threadArgs);
		if(returnValue != 0)
			DieWithUserMessage("pthread_create() failed", strerror(returnValue));
		printf("with thread %lu\n", (unsigned long int)threadID);
	}
}

void *ThreadMain(void *threadArgs)
{
	pthread_detach(pthread_self());

	int clntSock = ((struct ThreadArgs *) threadArgs)->clntSock;
	free(threadArgs);
	HandleTCPClient(clntSock);
	return (NULL);
}
