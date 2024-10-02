#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "EventLoop.h"
#include "InetAddress.h"
#include "Socket.h"
#include "Channel.h"
#include "Acceptor.h"
#include "Connection.h"
#include <functional>
#include <map>

class TcpServer {
private:
    EventLoop loop_;
    Acceptor* acceptor_;
    std::map<int, Connection*> connections_;
    std::function<void(Connection*)> new_connection_callback_;
    std::function<void(Connection*)> close_connection_callback_;
    std::function<void(Connection*)> error_connection_callback_;
    std::function<void(Connection*, std::string&)> process_message_callback_;
    std::function<void(Connection*)> send_complete_callback_;
    std::function<void(EventLoop*)> epoll_timeout_callback_;

public:
    TcpServer(const char* ip, uint16_t port);

    ~TcpServer();

    void start();

    void newConnection(Socket* client_socket);

    void closeConnection(Connection* connection);

    void errorConnection(Connection* connection);

    void processMessage(Connection* conn, std::string& message);

    void sendComplete(Connection* conn);

    void epollTimeout(EventLoop* loop);
    
    void setNewConnectionCallback(std::function<void(Connection*)> func);

    void setCloseConnectionCallback(std::function<void(Connection*)> func);

    void setErrorConnectionCallback(std::function<void(Connection*)> func);

    void setProcessMessageCallback(std::function<void(Connection*, std::string&)> func);

    void setSendCompleteCallback(std::function<void(Connection*)> func);

    void setEpollTimeoutCallback(std::function<void(EventLoop*)> func);
};

#endif
