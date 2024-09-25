#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "Epoll.h"
#include "Channel.h"

class Channel;
class Epoll;

class EventLoop {
private:
    Epoll* epoll_;

public:
    EventLoop();

    ~EventLoop();

    void run();

    void addChannel(Channel* channel);
};

#endif
