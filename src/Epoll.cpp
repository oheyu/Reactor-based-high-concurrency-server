#include "Epoll.h"


Epoll::Epoll() {
    epoll_fd_ = epoll_create(1);
    if (epoll_fd_ == -1) {
        std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__
            << "-> epoll_fd create error: " << std::strerror(errno) << std::endl;
        exit(-1);
    }
}

Epoll::~Epoll() {::close(epoll_fd_);}

void Epoll::collectInterests(int fd, uint32_t op) {
    struct epoll_event interest_event;
    interest_event.data.fd = fd;
    interest_event.events = op;       // Adopt default LT.

    if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &interest_event) == -1) {
        std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__
            << "-> epoll_ctl() error: " << std::strerror(errno) << std::endl;
        exit(-1);
    }
}

std::vector<epoll_event> Epoll::loop(int timeout) {
    std::vector<epoll_event> get_events;

    bzero(events_, sizeof(events_));

    int in_fd {epoll_wait(epoll_fd_, events_, MAX_EVENTS, timeout)};

    if (in_fd == -1) {
        std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__
            << "-> epoll_wait() error: " << std::strerror(errno) << std::endl;
        exit(-1);
    }
    if (in_fd == 0) {
        std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__ << "-> time out" << std::endl;
        return get_events;
    }

    for (int i {0}; i < in_fd; ++i) {get_events.push_back(events_[i]);}

    return get_events;
}
