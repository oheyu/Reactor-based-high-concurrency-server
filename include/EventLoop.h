#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "Epoll.h"
#include "Channel.h"
#include <functional>

class Channel;
class Epoll;

class EventLoop {
private:
    Epoll* epoll_;
    std::function<void(EventLoop*)> epoll_timeout_callback_;

public:
    EventLoop();

    ~EventLoop();

    void run();

    void addChannel(Channel* channel);

    void setEpollTimeoutCallback(std::function<void(EventLoop*)> func);
};

#endif
