#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include "TcpServer.h"
#include "ThreadPool.h"
#include <unistd.h>
#include <sys/syscall.h>

class EchoServer {
private:
    TcpServer tcp_server_;
    ThreadPool thread_pool_;

public:
    EchoServer(const char* ip, uint16_t port, int io_threads = 3, int work_threads = 5);

    ~EchoServer();

    void lanch();

    void handleNewConnection(spConnection conn);

    void handleCloseConnection(spConnection conn);

    void handleErrorConnection(spConnection conn);

    void handleProcessMessage(spConnection conn, std::string& message);

    void onMessage(spConnection conn, std::string& message);

    void handleSendComplete(spConnection conn);

    void handleEpollTimeout(EventLoop* loop);
};

#endif // !ECHOSERVER_H
