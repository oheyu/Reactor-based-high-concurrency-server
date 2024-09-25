#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "Epoll.h"

class EventLoop {
private:
    Epoll* epoll_;

public:
    EventLoop();

    ~EventLoop();

    void run();

    Epoll* createEpoll(); 
};

#endif
