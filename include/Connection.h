#ifndef CONNECTION_H
#define CONNECTION_H

#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "Buffer.h"
#include "TimeStamp.h"
#include <functional>
#include <memory>
#include <atomic>
#include <sys/syscall.h>
#include <unistd.h>

class Connection;
class EventLoop;
class Channel;

using spConnection = std::shared_ptr<Connection>;

class Connection : public std::enable_shared_from_this<Connection> {
private:
    EventLoop* loop_;
    Socket* client_socket_;
    std::unique_ptr<Channel> client_channel_;
    std::function<void(spConnection)> close_callback_;
    std::function<void(spConnection)> error_callback_;
    std::function<void(spConnection, std::string&)> process_message_callback_;
    std::function<void(spConnection)> send_complete_callback_;
    Buffer input_buffer_;
    Buffer output_buffer_;
    std::atomic_bool disconnect_;
    TimeStamp current_time_;

public:
    Connection(EventLoop* loop, Socket* client_socket);

    ~Connection();

    int fd() const;

    std::string ip() const;

    uint16_t port() const;

    void closeCallback();

    void errorCallback();

    void writeCallback();

    void setCloseCallback(std::function<void(spConnection)> fn);

    void setErrorCallback(std::function<void(spConnection)> fn);

    void onMessage();

    void setProcessMessageCallback (std::function<void(spConnection, std::string&)> fn);

    void setSendCompleteCallback (std::function<void(spConnection)> fn);

    void send(const char* data, size_t size);
    
    // void sendPlus(const char* data, size_t size);

    void sendPlus(std::shared_ptr<std::string> data);

    bool timeOut(time_t now, int val);
};

#endif // !CONNECTION_H
