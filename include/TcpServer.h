#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "EventLoop.h"
#include "InetAddress.h"
#include "Socket.h"
#include "Channel.h"
#include "Acceptor.h"
#include "Connection.h"
#include <mutex>
#include <functional>
#include <map>
#include <vector>
#include <ThreadPool.h>
#include <memory>

class TcpServer {
private:
    EventLoop* main_loop_;
    std::vector<EventLoop*> sub_loops_;
    ThreadPool* thread_pool_;
    std::mutex mutex_;
    int num_threads_;
    Acceptor* acceptor_;
    std::map<int, spConnection> connections_;
    std::function<void(spConnection)> new_connection_callback_;
    std::function<void(spConnection)> close_connection_callback_;
    std::function<void(spConnection)> error_connection_callback_;
    std::function<void(spConnection, std::string&)> process_message_callback_;
    std::function<void(spConnection)> send_complete_callback_;
    std::function<void(EventLoop*)> epoll_timeout_callback_;

public:
    TcpServer(const char* ip, uint16_t port, int num_threads);

    ~TcpServer();

    void start();

    void serverStop();

    void newConnection(Socket* client_socket);

    void closeConnection(spConnection connection);

    void errorConnection(spConnection connection);

    void processMessage(spConnection conn, std::string& message);

    void sendComplete(spConnection conn);

    void epollTimeout(EventLoop* loop);
    
    void setNewConnectionCallback(std::function<void(spConnection)> func);

    void setCloseConnectionCallback(std::function<void(spConnection)> func);

    void setErrorConnectionCallback(std::function<void(spConnection)> func);

    void setProcessMessageCallback(std::function<void(spConnection, std::string&)> func);

    void setSendCompleteCallback(std::function<void(spConnection)> func);

    void setEpollTimeoutCallback(std::function<void(EventLoop*)> func);

    void removeConn(int fd);
};

#endif
