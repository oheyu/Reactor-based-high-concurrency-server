#include "EventLoop.h"

EventLoop::EventLoop() : epoll_(new Epoll) {}

EventLoop::~EventLoop() {delete epoll_;}

void EventLoop::run() {
    while (true) {
        std::vector<Channel*> results {epoll_->loop()};
        for (auto& result : results) {result->handleEvent();}
    }
}

Epoll* EventLoop::createEpoll() { return epoll_; }
