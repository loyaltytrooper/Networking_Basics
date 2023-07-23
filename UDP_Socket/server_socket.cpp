// ! Intro to UDP
/*
    ? Universal Datagram Protocol
    ? Client and server don't maintain a constant connection
    ? Either can transmit a package
    ? Receiving app can determine who sent the package and respond accordingly
    ? There's no guarantee that the sent packet will reach destination or not
    ? Reduces the lag associated with TCP
*/

#include <cerrno>
#include <iostream>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <unistd.h>
#include <errno.h> 

#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define ARG_ACCEPT socklen_t
#define closesocket(s) close(s)

using namespace std;

int main()
{
    // SOCK_DGRAM type specification for UDP sockets
    // IPPORTO_UDP socket type specification for UDP sockets
    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (serverSocket == INVALID_SOCKET)
    {
        cout << "socket error " << errno << endl;
        cout << strerror(errno) << endl;
        close(serverSocket);
        return 0;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    addr.sin_port = htons(5555);

    if (bind(serverSocket, (sockaddr *)&addr, sizeof(sockaddr_in)) == SOCKET_ERROR)
    {
        cout << "socket error " << errno << endl;
        cout << strerror(errno) << endl;
        close(serverSocket);
        return 0;
    }

    // We won't be listening to any connections, so using sendTo to just send information
    // ! int sendTo(SOCKET s, const char *buf, int len, int flags, const struct sockaddr *to, int tolen);
    // ! is used to send data to a specific destination
    // s: a descriptor indentifying a (possibly connected) socket
    // buf: the data to be sent in serialized or char array format by casting objects or so
    // len: the length of the data to be sent
    // flags: specify the way in which the call is made
    // to: an optional pointer to sockaddr_in struct that contains the address of the targetted socket
    // tolen: the size in bytes of the address pointed to be the parameter
    // * if no error occurs, sendTo returns the totalNumber of bytes sent, else -1

    // ! almost similar code for recvfrom function

    char buf[] = "Hi arpan";
    int bytes = sendto(serverSocket, buf, strlen(buf), 0, (sockaddr *)&addr, sizeof(addr));
    if (bytes != -1)
    {
        cout << "socket error " << errno << endl;
        cout << strerror(errno) << endl;
        close(serverSocket);
        return 0;
    }
    else
    {
        cout << "Data Sent: ";
    }
    return 0;
}