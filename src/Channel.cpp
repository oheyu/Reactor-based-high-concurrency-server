#include "Channel.h"



Channel::Channel(EventLoop* loop, int fd) : loop_(loop), fd_(fd) {}

// For 'epoll_' and 'fd_', you should only use them, but do not destroy them.
Channel::~Channel() {}

int Channel::fd() const {return fd_;}

void Channel::enableEdgeTrigger() {events_ |= EPOLLET;}

void Channel::enableReading() {
    events_ |= EPOLLIN;
    loop_->addChannel(this);
}

void Channel::disableReading() {
    events_ &= ~EPOLLIN;
    loop_->addChannel(this);
}

void Channel::enableWriting() {
    events_ |= EPOLLOUT;
    loop_->addChannel(this);
}

void Channel::disableWriting() {
    events_ &= ~EPOLLOUT;
    loop_->addChannel(this);
}

void Channel::setInEpoll() {is_in_epoll_ = true;}

void Channel::setRevents(uint32_t event) {revents_ = event;}

bool Channel::isInEpoll() const {return is_in_epoll_;}

uint32_t Channel::events() const {return events_;}

uint32_t Channel::revents() const {return revents_;}

void Channel::handleEvent() {
    if (revents_ & EPOLLRDHUP) {
        close_callback_();exit(-1);
    } else if (revents_ & (EPOLLIN | EPOLLPRI)) {
        read_callback_();
    } else if (revents_ & EPOLLOUT) {
        write_callback_();
    } else {
        error_callback_();
    }
}

void Channel::setReadCallback(std::function<void()> func) {read_callback_ = func;}

void Channel::setCloseCallback(std::function<void()> func) {close_callback_ = func;}

void Channel::setErrorCallback(std::function<void()> func) {error_callback_ = func;}

void Channel::setWriteCallback(std::function<void()> func) {write_callback_ = func;}
