#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "../include/Practical.h"
#define MAXSTRINGLENGTH 1024

void UseIdleTime();
void SIGIOHandler(int signalType);

int servSock;

int main(int argc, char *argv[])
{
	if(argc != 2)
		DieWithUserMessage("Parameter(s)", "<Server Port/Service>");
	
	char *service = argv[1];

	struct addrinfo addrCriteria;
	memset(&addrCriteria, 0, sizeof(addrCriteria));
	addrCriteria.ai_family = AF_UNSPEC;
	addrCriteria.ai_flags = AI_PASSIVE;
	addrCriteria.ai_socktype = SOCK_DGRAM;
	addrCriteria.ai_protocol = IPPROTO_UDP;

	struct addrinfo *servAddr;
	int rtnVal = getaddrinfo(NULL, service, &addrCriteria, &servAddr);
	if(rtnVal != 0)
		DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));



	int servSock = socket(servAddr->ai_family, servAddr->ai_socktype, servAddr->ai_protocol);
	if(servSock < 0)
		DieWithSystemMessage("socket() failed");
	
	/* Bind to the local address */
	if(bind(servSock, servAddr->ai_addr, servAddr->ai_addrlen) < 0)
		DieWithSystemMessage("bind() failed");
	freeaddrinfo(servAddr);


	struct sigaction handler;
	handler.sa_handler = SIGIOHandler;
	if(sigfillset(&handler.sa_mask) < 0)
		DieWithSystemMessage("sigfillset() failed");
	handler.sa_flags = 0;

	if(sigaction(SIGIO, &handler, 0) < 0)
		DieWithSystemMessage("sigaction() failed for SIGIO");
	if(fcntl(servSock, F_SETOWN, getpid()) < 0)
		DieWithSystemMessage("Unable to set process owner to us");

	if(fcntl(servSock, F_SETFL, O_NONBLOCK|FASYNC) < 0)
		DieWithSystemMessage("Unable to put client sock into non-blocking/async mode");

	for(;;)
		UseIdleTime();

}

void UseIdleTime()
{
	puts(".");
	sleep(3);
}

void SIGIOHandler(int signalType)
{
	ssize_t numBytesRcvd;
	
	do 
	{
		struct sockaddr_storage clntAddr;
		size_t clntLen = sizeof(clntAddr);
		char buffer[MAXSTRINGLENGTH];

		numBytesRcvd = recvfrom(servSock, buffer, MAXSTRINGLENGTH, 0,
				(struct sockaddr *)&clntAddr, &clntLen);
	

		if(numBytesRcvd < 0)
		{
			if(errno != EWOULDBLOCK)
				DieWithSystemMessage("recvfrom() failed");
		}
		else
		{
			fprintf(stdout, "Handling client");
			PrintSocketAddress((struct sockaddr *)&clntAddr, stdout);
			fputc('\n', stdout);
		}


		ssize_t numBytesSent = sendto(servSock, buffer, numBytesRcvd, 0,
				(struct sockaddr *)&clntAddr, sizeof(clntAddr));
		if(numBytesSent < 0)
			DieWithSystemMessage("sendto() failed");
		else if(numBytesSent != numBytesRcvd)
			DieWithUserMessage("sendto()", "sent unexpected number of bytes");

	} while(numBytesRcvd >= 0);

}
