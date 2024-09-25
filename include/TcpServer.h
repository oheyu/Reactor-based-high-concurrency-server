#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "EventLoop.h"
#include "InetAddress.h"
#include "Socket.h"
#include "Channel.h"
#include "Acceptor.h"
#include "Connection.h"
#include <functional>

class TcpServer {
private:
    EventLoop loop_;
    Acceptor* acceptor_;

public:
    TcpServer(const char* ip, uint16_t port);

    ~TcpServer();

    void start();

    void newConnection(Socket* client_socket);
};

#endif
