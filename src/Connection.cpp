#include "Connection.h"

Connection::Connection(EventLoop* loop, Socket* client_socket) : loop_(loop), client_socket_(client_socket) {
    client_channel_ = new Channel(loop_, client_socket_->fd());
    client_channel_->setReadCallback(std::bind(&Connection::onMessage, this));
    client_channel_->setCloseCallback(std::bind(&Connection::closeCallback, this));
    client_channel_->setErrorCallback(std::bind(&Connection::errorCallback, this));
    client_channel_->enableEdgeTrigger();
    client_channel_->enableReading();
}

Connection::~Connection() {
    delete client_socket_;
    delete client_channel_;
}

int Connection::fd() const {return client_socket_->fd();}

std::string Connection::ip() const {return client_socket_->ip();}

uint16_t Connection::port() const {return client_socket_->port();}

void Connection::closeCallback() {close_callback_(this);}

void Connection::errorCallback() {error_callback_(this);}

void Connection::setCloseCallback(std::function<void(Connection*)> fn) {close_callback_ = fn;}

void Connection::setErrorCallback(std::function<void(Connection*)> fn) {error_callback_ = fn;}

void Connection::onMessage() {
    char buffer[1024];
    while (true) {
        std::memset(buffer, 0, sizeof(buffer));
        ssize_t readn {recv(fd(), buffer, sizeof(buffer), 0)};
        if (readn > 0) {
            input_buffer_.append(buffer, readn);
        } else if (readn == -1 && errno == EINTR) {       // Interrupt.
            continue;
        } else if (readn == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) {        // No data.
            std::cout << "Receive \"" << input_buffer_.data() << "\" from " << fd() << std::endl;
            output_buffer_ = input_buffer_;
            input_buffer_.clear();
            send(fd(), output_buffer_.data(), output_buffer_.size(), 0);
            break;
        } else if (readn == 0) {
            closeCallback(); break;
        }
    }
}
