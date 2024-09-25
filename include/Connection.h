#ifndef CONNECTION_H
#define CONNECTION_H

#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"

class EventLoop;
class Channel;
class Socket;

class Connection {
private:
    EventLoop* loop_;
    Socket* client_socket_;
    Channel* client_channel_;

public:
    Connection(EventLoop* loop, Socket* client_socket);

    ~Connection();
};

#endif // !CONNECTION_H
