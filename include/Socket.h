#ifndef SOCKET_H
#define SOCKET_H

#include "InetAddress.h"
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>


int createNonBlock();


class Socket {
private:
    const int fd_;

public:
    Socket(int fd);

    ~Socket();

    int getFd() const;

    void setReuseAddr(bool toggle);

    void setReusePort(bool toggle);

    void setTcpNoDelay(bool toggle);

    void setKeepAlive(bool toggle);

    void bind(const InetAddress& server_address);

    void listen(int backlog = 128);

    int accept(InetAddress& client_address);

};

#endif
