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
#include <cstdint>


int createNonBlock();


class Socket {
private:
    const int fd_;
    std::string ip_;
    uint16_t port_;

public:
    Socket(int fd);

    ~Socket();

    int fd() const;

    std::string ip() const;

    uint16_t port() const;

    void setReuseAddr(bool toggle);

    void setReusePort(bool toggle);

    void setTcpNoDelay(bool toggle);

    void setKeepAlive(bool toggle);

    void bind(const InetAddress& server_address);

    void listen(int backlog = 128);

    int accept(InetAddress& client_address);

};

#endif
