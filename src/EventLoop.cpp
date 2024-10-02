#include "EventLoop.h"

EventLoop::EventLoop() : epoll_(new Epoll) {}

EventLoop::~EventLoop() {delete epoll_;}

void EventLoop::run() {
    while (true) {
        std::vector<Channel*> results {epoll_->loop()};
        if (results.size() == 0) epoll_timeout_callback_(this);
        for (auto& result : results) {result->handleEvent();}
    }
}

void EventLoop::addChannel(Channel* channel) {
    epoll_->addChannel(channel);
}

void EventLoop::setEpollTimeoutCallback(std::function<void(EventLoop*)> func) {
    epoll_timeout_callback_ = func;
}
