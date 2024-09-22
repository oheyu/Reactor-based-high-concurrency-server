#include "Socket.h"


int createNonBlock() {
    int listen_fd {socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK, IPPROTO_TCP)};
    if (listen_fd == -1) {
        std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__
            << "-> listen socket create error: " << std::strerror(errno) << std::endl;
        exit(-1);
    }
    return listen_fd;
}

Socket::Socket(int fd): fd_(fd) {} 

Socket::~Socket() {::close(fd_);}

int Socket::getFd() const {return fd_;}

void Socket::setReuseAddr(bool toggle) {
    int opt = toggle ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, static_cast<socklen_t>(sizeof(opt)));
}

void Socket::setReusePort(bool toggle) {
    int opt = toggle ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, TCP_NODELAY, &opt, static_cast<socklen_t>(sizeof(opt))); // Disable Naggle
}

void Socket::setTcpNoDelay(bool toggle) {
    int opt = toggle ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT, &opt, static_cast<socklen_t>(sizeof(opt)));
}

void Socket::setKeepAlive(bool toggle) {
    int opt = toggle ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_KEEPALIVE, &opt, static_cast<socklen_t>(sizeof(opt)));
}

void Socket::bind(const InetAddress& server_address) {
    if (::bind(fd_, server_address.addr(), sizeof(struct sockaddr)) == -1) {
        std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__
            << "-> bind socket error: " << std::strerror(errno) << std::endl;
        ::close(fd_); exit(-1);
    }
}

void Socket::listen(int backlog) {
    // Set 'backlog' in listen() to be a little bigger if you need high-concurrency.
    if (::listen(fd_, backlog) == -1) {
        std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__
            << "-> listen socket error: " << std::strerror(errno) << std::endl;
        ::close(fd_); exit(-1);
    } else {
        std::cout << "Listening on " << fd_ << "..." << std::endl;
    }
}

int Socket::accept(InetAddress& client_address) {
    struct sockaddr_in peer_address;
    socklen_t length {static_cast<socklen_t>(sizeof(peer_address))};
    int client_fd {::accept4(fd_, (struct sockaddr*)(&peer_address), &length, SOCK_NONBLOCK)};
    client_address.setAddress(peer_address);
    return client_fd;
}
