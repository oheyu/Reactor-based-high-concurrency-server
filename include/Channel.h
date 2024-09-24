#ifndef CHANNEL_H
#define CHANNEL_H

#include "Epoll.h"
#include "InetAddress.h"
#include "Socket.h"
#include <sys/socket.h>
#include <cstdint>
#include <functional>


class Epoll;

class Channel {
private:
    int fd_ {-1};
    Epoll* epoll_ {nullptr};
    bool is_in_epoll_ {false};
    uint32_t events_ {0};
    uint32_t revents_ {0};
    std::function<void()> read_callback_;

public:
    Channel(Epoll* epoll, int fd);

    ~Channel();

    int fd() const;

    void enableEdgeTrigger();

    void enableReading();

    void setInEpoll();

    void setRevents(uint32_t event);

    bool isInEpoll() const;

    uint32_t events() const;

    uint32_t revents() const;

    void handleEvent();

    void newConnection(Socket* Server_socket);

    void onMessage();

    void setReadCallback(std::function<void()> func);
};

#endif // !CHANNEL_H
