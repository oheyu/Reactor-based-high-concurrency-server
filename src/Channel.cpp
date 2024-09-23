#include "Channel.h"



Channel::Channel(Epoll* epoll, int fd, bool is_listen) : epoll_(epoll), fd_(fd), is_listen_(is_listen){}

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

void Channel::handleEvent(Socket* server_socket) {
    if (revents_ & EPOLLRDHUP) {
        std::cerr << "Client @ " << fd_ << " disconnect." << std::endl;
        close(fd_); exit(-1);
    } else if (revents_ & (EPOLLIN | EPOLLPRI)) {
        if (is_listen_) {
            InetAddress client_address;
            Socket* client_socket {new Socket(server_socket->accept(client_address))};
            if (client_socket->fd() == -1) {
                std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__
                    << "-> connection error: " << std::strerror(errno) << std::endl;
                exit(-1);
            }
            std::cout << "Establish connection with <" << client_address.ip() 
                << "> on <" << client_address.port() << "> using <" << client_socket->fd() << ">" << std::endl;

            Channel* client_channel {new Channel(epoll_, client_socket->fd(), false)};
            client_channel->enableEdgeTrigger();
            client_channel->enableReading();
        } else {
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
                    std::cerr << "Client # " << fd_ << " disconnect." << std::endl;
                    close(fd_); break;
                }
            }
        }
    } else if (revents_ & EPOLLOUT) {
        // Accomplish later.
    } else {
        std::cerr << "Error on " << fd_ << " anyway" << std::endl;
        close(fd_);
    }
}
