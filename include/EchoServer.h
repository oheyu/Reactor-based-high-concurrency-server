#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include "TcpServer.h"

class EchoServer {
private:
    TcpServer tcp_server_;

public:
    EchoServer(const char* ip, uint16_t port);

    ~EchoServer();

    void lanch();

    void handleNewConnection(Connection* conn);

    void handleCloseConnection(Connection* conn);

    void handleErrorConnection(Connection* conn);

    void handleProcessMessage(Connection* conn, std::string& message);

    void handleSendComplete(Connection* conn);

    void handleEpollTimeout(EventLoop* loop);
};

#endif // !ECHOSERVER_H
