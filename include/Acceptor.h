#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "Connection.h"
#include <functional>
#include <memory>

class Acceptor {
private:
    EventLoop* loop_;
    Socket server_socket_;
    Channel accept_channel_;
    std::function<void(Socket*)> new_connection_;

public:
    Acceptor(EventLoop* loop, const char* ip, uint16_t port);

    ~Acceptor();

    void newConnection();

    void setNewConnection(std::function<void(Socket*)> fn);
};

#endif // !ACCEPTOR_H
