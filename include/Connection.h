#ifndef CONNECTION_H
#define CONNECTION_H

#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "Buffer.h"
#include <functional>

class EventLoop;
class Channel;
class Socket;

class Connection {
private:
    EventLoop* loop_;
    Socket* client_socket_;
    Channel* client_channel_;
    std::function<void(Connection*)> close_callback_;
    std::function<void(Connection*)> error_callback_;
    Buffer input_buffer_;
    Buffer output_buffer_;

public:
    Connection(EventLoop* loop, Socket* client_socket);

    ~Connection();

    int fd() const;

    std::string ip() const;

    uint16_t port() const;

    void closeCallback();

    void errorCallback();

    void setCloseCallback(std::function<void(Connection*)> fn);

    void setErrorCallback(std::function<void(Connection*)> fn);

    void onMessage();
};

#endif // !CONNECTION_H
