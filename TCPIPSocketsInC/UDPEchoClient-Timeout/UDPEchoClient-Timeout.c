#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "../include/Practical.h"
#define MAXSTRINGLENGTH 1024

static const unsigned int TIMEOUT_SECS = 2;
static const unsigned int MAXTRIES = 5;

unsigned int tries = 0;
void CatchAlarm(int ignored);

int main(int argc, char *argv[])
{
	if(argc < 3 || argc > 4)
		DieWithUserMessage("Parameter(s)", "<Server Address> <Echo Word> [<Server Port>]");

	char *server = argv[1];
	char *echoString = argv[2];

	size_t echoStringLen = strlen(echoString);
	if(echoStringLen > MAXSTRINGLENGTH)
		DieWithUserMessage(echoString, "string too long");

	char *service = (argc == 4) ? argv[3]: "echo";
	struct addrinfo addrCriteria;
	memset(&addrCriteria, 0, sizeof(addrCriteria));
	addrCriteria.ai_family = AF_UNSPEC;
	addrCriteria.ai_socktype = SOCK_DGRAM;
	addrCriteria.ai_protocol = IPPROTO_UDP;


	struct addrinfo *servAddr;
	int rtnVal = getaddrinfo(server, service, &addrCriteria, &servAddr);
	if(rtnVal != 0)
		DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));


	int sock = socket(servAddr->ai_family, servAddr->ai_socktype, servAddr->ai_protocol);
	if(sock < 0)
		DieWithSystemMessage("socket() failed");


	struct sigaction handler;
	handler.sa_handler = CatchAlarm;
	if(sigfillset(&handler.sa_mask) < 0)
		DieWithSystemMessage("sigfillset() failed");
	handler.sa_flags = 0;

	if(sigaction(SIGALRM, &handler, 0) < 0)
		DieWithSystemMessage("sigaction() failed for SIGALRM");



	ssize_t numBytes = sendto(sock, echoString, echoStringLen, 0, servAddr->ai_addr, servAddr->ai_addrlen);
	if(numBytes < 0)
		DieWithSystemMessage("sendto() failed");
	else if(numBytes != echoStringLen)
		DieWithUserMessage("sendto() error", "sent unexpected number of bytes");

	/* Receive a response */

	struct sockaddr_storage fromAddr;
	socklen_t fromAddrLen = sizeof(fromAddr);
	alarm(TIMEOUT_SECS);
	char buffer[MAXSTRINGLENGTH+1];

	while((numBytes = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0, 
					(struct sockaddr *)&fromAddr, &fromAddrLen)) < 0);
	{
		if(errno == EINTR)
		{
			if(tries < MAXTRIES)
			{
				numBytes = sendto(sock, echoString, echoStringLen, 0, 
						servAddr->ai_addr, servAddr->ai_addrlen);
				if(numBytes < 0)
					DieWithSystemMessage("sendo() failed");
				else if(numBytes != echoStringLen)
					DieWithUserMessage("sendto() error", "sent unexpected number of bytes");

			}
			else
				DieWithUserMessage("No Response", "unable to communicate with server");
		}	
		else
			DieWithSystemMessage("recvfrom() failed");
	}
	alarm(0);

	buffer[echoStringLen] = '\0';
	printf("Received: %s\n", buffer);

	close(sock);
	exit(0);
}

void CatchAlarm(int ignored)
{
	tries += 1;
}
