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
        // Accomplish later.
    } else {
        error_callback_();
    }
}

void Channel::onMessage() {
    char buffer[1024];
    while (true) {
        bzero(buffer, sizeof(buffer));
        ssize_t readn {recv(fd_, buffer, sizeof(buffer), 0)};
        if (readn > 0) {
            std::string message(buffer);
            std::cout << "Receive \"" << message << "\" from " << fd_ << std::endl;
            send(fd_, buffer, sizeof(buffer), 0);
        } else if (readn == -1 && errno == EINTR) {       // Interrupt.
            continue;
        } else if (readn == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) {        // No data.
            break;
        } else if (readn == 0) {
            error_callback_(); break;
        }
    }
}

void Channel::setReadCallback(std::function<void()> func) {read_callback_ = func;}

void Channel::setCloseCallback(std::function<void()> func) {close_callback_ = func;}

void Channel::setErrorCallback(std::function<void()> func) {error_callback_ = func;}
