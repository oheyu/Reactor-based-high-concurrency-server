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

void Epoll::addChannel(Channel* channel) {
    struct epoll_event interest_event;
    interest_event.data.ptr = channel;
    interest_event.events = channel->events();
    if (channel->isInEpoll()) {
        if (epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, channel->fd(), &interest_event) == -1) {
            std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__
                << "-> epoll_ctl() error: " << std::strerror(errno) << std::endl;
            exit(-1);
        }
    } else {
        if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, channel->fd(), &interest_event) == -1) {
            std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__
                << "-> epoll_ctl() error: " << std::strerror(errno) << std::endl;
            exit(-1);
        }
        channel->setInEpoll();
    }
}

std::vector<Channel*> Epoll::loop(int timeout) {
    std::vector<Channel*> get_channels;

    bzero(events_, sizeof(events_));

    int in_fd {epoll_wait(epoll_fd_, events_, MAX_EVENTS, timeout)};

    if (in_fd == -1) {
        std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__
            << "-> epoll_wait() error: " << std::strerror(errno) << std::endl;
        exit(-1);
    }
    if (in_fd == 0) {
        std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__ << "-> time out" << std::endl;
        return get_channels;
    }

    for (int i {0}; i < in_fd; ++i) {
        Channel* channel {reinterpret_cast<Channel*>(events_[i].data.ptr)};
        channel->setRevents(events_[i].events);
        get_channels.push_back(channel);
    }

    return get_channels;
}
