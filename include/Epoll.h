#ifndef EPOLL_H
#define EPOLL_H

#include "Channel.h"
#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <vector>


class Channel;

class Epoll {
private:
    static const int MAX_EVENTS {100};
    int epoll_fd_ = -1;
    epoll_event events_[MAX_EVENTS];

public:
    Epoll();

    ~Epoll();
    
    void addChannel(Channel* channel);

    void removeChannel(Channel* channel);

    std::vector<Channel*> loop(int timeout = -1);
};

#endif // !EPOLL_H
