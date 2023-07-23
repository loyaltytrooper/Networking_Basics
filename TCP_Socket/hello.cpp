#include <cerrno>
#include <iostream>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <unistd.h>
#include <errno.h>
#include "dataModel.h"

#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define ARG_ACCEPT socklen_t
#define closesocket(s) close(s)

using namespace std;

int main()
{
    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
    {
        cout << errno << "socket error" << endl;
        cout << strerror(errno) << endl;
        close(serverSocket);
        return 0;
    }
    else
    {
        cout << "Socket initialized successfully" << endl;
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &service.sin_addr.s_addr);
    service.sin_port = htons(8080);

    if (bind(serverSocket, (sockaddr *)&service, sizeof(service)) == SOCKET_ERROR)
    {
        cout << "bind() failed" << endl
             << strerror(errno) << endl
             << "Failed to bind socket to ip address and port" << endl;
        close(serverSocket);
        return 0;
    }
    else
    {
        cout << "binded" << endl;
    }

    if (listen(serverSocket, 10) != SOCKET_ERROR)
    {
        cout << "Listening on port 8080 " << endl;
    }
    else
    {
        cout << "Failed to listen" << endl;
        cout << strerror(errno) << endl;
        close(serverSocket);
        return 0;
    }

    // The send() function sends data to the connected socket
    // int send(SOCKET s, const char* buf, int len, int flags);
    // len: len of the char buffer
    // flags: optional set of flags that influences the behaviour of this function
    // if no error send returns the number of the bytes send, else SOCKET_ERROR is returned

    SOCKET acceptSocket;
    acceptSocket = accept(serverSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET)
    {
        cout << "client connection accept failed" << endl;
        cout << strerror(errno) << endl;
    }

    // ! int recv(SOCKET s, char *buf, int len, int flags) function to recieve the data from a connected socket
    // S: descriptor to signify the connected socket
    // buf: buffer to receive the data from
    // len: length of the data to be received
    // flags: flags to control how long the socket is connected to the server
    // * if no error occurs, returns the number of bytes received,
    // * if the connection is closed gracefully, the return value is zero else SOCKET_ERROR

    // ! receiving string buffer from a connected socket
    // char buf[200];
    // int bytes = recv(acceptSocket, &buf, 200, 0);

    // ! receiving an object from a connected socket
    Data data;
    int bytes = recv(acceptSocket, (char *)&data, sizeof(Data), 0);

    if (bytes == 0)
    {
        cout << "Connection is closed" << endl
             << strerror(errno) << endl;
    }
    else if (bytes == SOCKET_ERROR)
    {
        cout << "Socket error" << endl
             << strerror(errno) << endl;
    }
    else
    {
        cout << "Data accepted" << endl
             << bytes << endl
             << data.health << endl;
    }

    int closeCall = closesocket(acceptSocket);
    return 0;
}