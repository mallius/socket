#include "../include/Practical.h"

#define BUFSIZE 1024

static const int MAXPENDING = 5;

int main(int argc, char *argv[])
{
	if(argc != 2) DieWithUserMessage("Parameters(s)", "<Server Port>");
	char *service = argv[1];	
	printf("servPort:[%s]\n", service);

	int servSock;
	if((servSock = SetupTCPServerSocket(service) < 0))
		DieWithUserMessage("SetupTCPServerSocket() failed", service);


	for(;;){					/* Run forever */

		/* Wait for a client to connect */
		int clntSock = AcceptTCPConnection(servSock);

		HandleTCPClient(clntSock);
		close(clntSock);
	}
}
