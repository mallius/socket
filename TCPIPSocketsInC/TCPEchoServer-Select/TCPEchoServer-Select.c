#include "../include/Practical.h"

int main(int argc, char *argv[])
{
	if(argc < 3) 
		DieWithUserMessage("Parameters(s)", "<Server Port>");
	long timeout = atol(argv[1]);
	int noPorts = argc - 2;

	int servSock[noPorts];
	int maxDescriptor = -1;

	int port = 0;
	for(port = 0; port < noPorts; port++)
	{
		servSock[port] = SetupTCPServerSocket(argv[port + 2]);
		if(servSock[port] > maxDescriptor)
			maxDescriptor = servSock[port];
	}
	puts("Starting server: Hit return to shutdown");
	bool running = true;
	fd_set sockSet;
	while(running)
	{
		FD_ZERO(&sockSet);
		FD_SET(STDIN_FILENO, &sockSet);
		int port;
		for(port = 0; port < noPorts; port++)
		{
			FD_SET(servSock[port], &sockSet);
		}
		struct timeval selTimeout;
		selTimeout.tv_sec = timeout;
		selTimeout.tv_usec = 0;

		if(select(maxDescriptor+1, &sockSet, NULL, NULL, &selTimeout) == 0)
			printf("No echo requests for %ld secs...Server still alive\n", timeout);
		else
		{
			if(FD_ISSET(0, &sockSet))
			{
				puts("Shutting down server");
				getchar();
				running = false;
			}
			int port;
			for(port = 0; port < noPorts; port++)
			
				if(FD_ISSET(servSock[port], &sockSet))
				{
					printf("Request on port %d: ", port);
					HandleTCPClient(AcceptTCPConnection(servSock[port]));
				}
			

		}
		
	}
	for(port = 0; port < noPorts; port++)
		close(servSock[port]);
	exit(0);
}
