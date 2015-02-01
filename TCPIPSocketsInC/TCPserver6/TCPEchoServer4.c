#include "../include/Practical.h"

#define BUFSIZE 1024

static const int MAXPENDING = 5;

int main(int argc, char *argv[])
{
	if(argc != 2) DieWithUserMessage("Parameters(s)", "<Server Port>");
	in_port_t servPort = atoi(argv[1]);			/* First argument: local port */
	printf("servPort:[%d]\n", servPort);

	int servSock;
	if((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithSystemMessage("socket() failed");

	/* Construct local address structure */
	struct sockaddr_in servAddr;			/* Local address */
	memset(&servAddr, 0, sizeof(servAddr));		/* Zero out Construct */
	servAddr.sin_family = AF_INET;			/* IPv4 address family */
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);	/* Any incoming interface */
	servAddr.sin_port = htons(servPort);		/* Local Port */
	
	/* Bind to the Local address */
	if(bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
		DieWithSystemMessage("bind() failed");

	/* Mark the socket so it will listen for incoming connections */
	if(listen(servSock, MAXPENDING) < 0)
		DieWithSystemMessage("listen() failed");

	for(;;){					/* Run forever */
		struct sockaddr_in clntAddr; 		/* Client address */
		socklen_t clntAddrLen = sizeof(clntAddr);

		/* Wait for a client to connect */
		int clntSock = accept(servSock, (struct sockaddr*)&clntAddr, &clntAddrLen);
		if(clntSock < 0)
		{
			DieWithSystemMessage("accept() failed");
		}

		/* clntSock is connected to a client */
		char clntName[INET_ADDRSTRLEN];
		if(inet_ntop(AF_INET, &clntAddr.sin_addr.s_addr, clntName, sizeof(clntName)) != NULL)
			printf("Handling client %s/%d\n", clntName, ntohs(clntAddr.sin_port));
		else
			puts("Unable to get client address");
		HandleTCPClient(clntSock);
	}
}
