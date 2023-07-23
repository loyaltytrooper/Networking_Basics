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
    // socket initialization
    SOCKET s = SOCKET_ERROR;
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        cout << "Error initializing socket" << endl
             << strerror(errno) << endl;
        return 0;
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    inet_pton(service.sin_family, "127.0.0.1", &service.sin_addr.s_addr);
    service.sin_port = htons(8080);

    if (connect(s, (sockaddr *)&service, sizeof(service)) == SOCKET_ERROR)
    {
        cout << "Not Connected" << endl
             << strerror(errno) << endl;
    }

    cout << "Connected" << endl;

    // ! Send(SOCKET s, const char *buf, int len, int flags)
    // the send function sends data to the connected socket
    // s: the socket to send data to (that has active connection
    // buf: the data to send
    // len: the length of the buffer data in bytes pointed to by buf parameter
    // flags: optional set of flags that influence the behaviour of the send function (e.g. no routing etc.)
    // ? if no error occurs then the send function returns the number fo bytes sent, else returns SOCKET_ERROR in case of error

    // sending string
    // char buffer[200];
    // cout << "Enter the data" << endl;
    // cin.getline(buffer, 200);

    // ! sending objects from socket by casting it to string type
    Data data = Data();
    data.health = 90;

    int byteCount = send(s, (char *)&data, sizeof(Data), 0);

    if (byteCount == SOCKET_ERROR)
    {
        cout << "Error sending data to socket" << endl
             << strerror(errno) << endl;
        return -1;
    }
    printf("%d bytes sent to the socket", byteCount);
    return 0;
}