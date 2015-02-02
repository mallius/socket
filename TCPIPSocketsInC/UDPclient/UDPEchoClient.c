#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include "../include/Practical.h"
#define MAXSTRINGLENGTH 1024

int main(int argc, char *argv[])
{
	if(argc < 3 || argc > 4)
		DieWithUserMessage("Parameter(s)", "<Server Address> <Echo Word> [<Server Port>]");

	char *servIP = argv[1];
	char *echoString = argv[2];

	size_t echoStringLen = strlen(echoString);
	if(echoStringLen > MAXSTRINGLENGTH)
		DieWithUserMessage(echoString, "string too long");

	char *servPort = (argc == 4) ? argv[3]: "echo";
	struct addrinfo addrCriteria;
	memset(&addrCriteria, 0, sizeof(addrCriteria));
	addrCriteria.ai_socktype = AF_UNSPEC;
	addrCriteria.ai_socktype = SOCK_DGRAM;
	addrCriteria.ai_protocol = IPPROTO_UDP;


	struct addrinfo *servAddr;
	int rtnVal = getaddrinfo(servIP, servPort, &addrCriteria, &servAddr);
	if(rtnVal != 0)
		DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));


	int sock = socket(servAddr->ai_family, servAddr->ai_socktype, servAddr->ai_protocol);
	if(sock < 0)
		DieWithSystemMessage("socket() failed");



	ssize_t numBytes = sendto(sock, echoString, echoStringLen, 0, servAddr->ai_addr, servAddr->ai_addrlen);
	if(numBytes < 0)
		DieWithSystemMessage("sendto() failed");
	else if(numBytes != echoStringLen)
		DieWithUserMessage("sendto() error", "sent unexpected number of bytes");

	/* Receive a response */

	struct sockaddr_storage fromAddr;
	socklen_t fromAddrLen = sizeof(fromAddr);
	char buffer[MAXSTRINGLENGTH+1];
	numBytes = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0, (struct sockaddr *)&fromAddr, &fromAddrLen);
	
	if(numBytes < 0)
		DieWithSystemMessage("recvfrom() failed");
	else if(numBytes != echoStringLen)
		DieWithUserMessage("recvfrom() error", "received unexpected number of bytes");

#if 0
	if(!SockAddrsEqual(servAddr->ai_addr, (struct sockaddr *)&fromAddr))
		DieWithUserMessage("recvfrom()", "received a packet from unknown source");
#endif	

	freeaddrinfo(servAddr);

	buffer[echoStringLen] = '\0';
	printf("Received: %s\n", buffer);

	close(sock);
	exit(0);
}
