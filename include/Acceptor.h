#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"

class Acceptor {
private:
    EventLoop* loop_;
    Socket* server_socket_;
    Channel* accept_channel_;

public:
    Acceptor(EventLoop* loop, const char* ip, uint16_t port);

    ~Acceptor();
};

#endif // !ACCEPTOR_H
