#include "client.h"

int main(void) {
    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    int status;
    const char * host_name = "pb-homework.appspot.com";
    char buffer[MAXBUFLEN];
    memset(buffer,0,MAXBUFLEN);
    status = WSAStartup(MAKEWORD(2, 2), &Data);
    if(status != 0)
    {
        printf("ERROR: WSAStartup unsuccessful\r\n");
        return 0;
    }

    recvSockAddr = newSockAddr(host_name);
    recvSocket = newSocket();
    connectToTheServer(recvSockAddr, recvSocket);

    sendRequest(recvSocket, host_name, "");
    recieveResponse(recvSocket, buffer, status);

	char * secret = strstr(buffer, "secret");

	int len_jump = strlen(buffer) - strlen(secret);

	sendRequest(recvSocket, host_name, secret);
    recieveResponse(recvSocket, buffer, status);

    char * content = buffer + len_jump;
    printf("%s\r\n",content);

    sendResultRequest(recvSocket, host_name, content);
    printf("Result: %d\n", ColumnWithMaxSum(content));

    memset(buffer, 0, MAXBUFLEN);

    recieveResponse(recvSocket, buffer, status);
    printf("%s\n", buffer);
    return 0;
}

