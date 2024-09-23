#ifndef CHANNEL_H
#define CHANNEL_H

#include "Epoll.h"
#include "InetAddress.h"
#include "Socket.h"
#include <sys/socket.h>
#include <cstdint>


class Epoll;

class Channel {
private:
    int fd_ {-1};
    Epoll* epoll_ {nullptr};
    bool is_in_epoll_ {false};
    uint32_t events_ {0};
    uint32_t revents_ {0};
    bool is_listen_ {false};

public:
    Channel(Epoll* epoll, int fd, bool is_listen);

    ~Channel();

    int fd() const;

    void enableEdgeTrigger();

    void enableReading();

    void setInEpoll();

    void setRevents(uint32_t event);

    bool isInEpoll() const;

    uint32_t events() const;

    uint32_t revents() const;

    void handleEvent(Socket* server_socket);
};

#endif // !CHANNEL_H
