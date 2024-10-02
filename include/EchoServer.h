#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include "TcpServer.h"
#include <unistd.h>
#include <sys/syscall.h>

class EchoServer {
private:
    TcpServer tcp_server_;

public:
    EchoServer(const char* ip, uint16_t port, int num_threads = 3);

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
