#include "Channel.h"



Channel::Channel(Epoll* epoll, int fd) : epoll_(epoll), fd_(fd) {}

// For 'epoll_' and 'fd_', you should only use them, but do not destroy them.
Channel::~Channel() {}

int Channel::fd() const {return fd_;}

void Channel::enableEdgeTrigger() {events_ |= EPOLLET;}

void Channel::enableReading() {
    events_ |= EPOLLIN;
    epoll_->addChannel(this);
}

void Channel::setInEpoll() {is_in_epoll_ = true;}

void Channel::setRevents(uint32_t event) {revents_ = event;}

bool Channel::isInEpoll() const {return is_in_epoll_;}

uint32_t Channel::events() const {return events_;}

uint32_t Channel::revents() const {return revents_;}
