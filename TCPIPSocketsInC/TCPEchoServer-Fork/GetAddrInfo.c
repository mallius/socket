#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include "../include/Practical.h"

int main(int argc, char *argv[])
{
	if(argc != 3)
		DieWithUserMessage("Parameter(s", "<Address/Name> <Port/Service>");
	char *addrString = argv[1];
	char *portString = argv[2];

	struct addrinfo addrCriteria;
	memset(&addrCriteria, 0, sizeof(addrCriteria));
	addrCriteria.ai_family = AF_UNSPEC;
	addrCriteria.ai_socktype = SOCK_STREAM;
	addrCriteria.ai_protocol = IPPROTO_TCP;

	struct addrinfo *addrList;
	struct addrinfo *addr;
	int rtnVal = getaddrinfo(addrString, portString, &addrCriteria, &addrList);

	if(rtnVal != 0)
		DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));
	for(addr = addrList; addr != NULL; addr = addr->ai_next)
	{
		PrintSocketAddress(addr->ai_addr, stdout);
		fputc('\n', stdout);
	}
	freeaddrinfo(addrList);
	exit(0);
}
