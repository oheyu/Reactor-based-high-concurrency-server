#ifndef EPOLL_H
#define EPOLL_H

#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <vector>


class Epoll {
private:
    static const int MAX_EVENTS {100};
    int epoll_fd_ = -1;
    epoll_event events_[MAX_EVENTS];

public:
    Epoll();

    ~Epoll();
    
    void collectInterests(int fd, uint32_t op);

    std::vector<epoll_event> loop(int timeout = -1);
};

#endif // !EPOLL_H
