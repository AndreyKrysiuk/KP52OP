#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480

int ColumnWithMaxSum(char * matrix);
SOCKET newSocket();
SOCKADDR_IN newSockAddr(const char * host_name);
void connectToTheServer(SOCKADDR_IN recvSockAddr, SOCKET recvSocket);
void sendRequest(SOCKET recvSocket, const char * host_name, char * content);
void sendResultRequest(SOCKET recvSocket, const char * host_name, char * content);
void recieveResponse(SOCKET recvSocket, char * buffer, int status);
#endif // CLIENT_H_INCLUDED
