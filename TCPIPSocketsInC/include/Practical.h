#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void DieWithSystemMessage(const char *msg);
void DieWithUserMessage(const char *msg, const char *detail);
void PrintSocketAddress(const struct sockaddr *address, FILE *stream);
int SetupTCPClientSocket(const char *host, const char *service);
int SetupTCPServerSocket(const char *service);
int AcceptTCPConnection(int servSock);
void HandleTCPClient(int clntSocket);
