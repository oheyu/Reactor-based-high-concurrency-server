#include "Connection.h"

Connection::Connection(EventLoop* loop, Socket* client_socket) : loop_(loop), client_socket_(client_socket) {
    client_channel_ = new Channel(loop_, client_socket_->fd());
    client_channel_->setReadCallback(std::bind(&Connection::onMessage, this));
    client_channel_->setCloseCallback(std::bind(&Connection::closeCallback, this));
    client_channel_->setErrorCallback(std::bind(&Connection::errorCallback, this));
    client_channel_->setWriteCallback(std::bind(&Connection::writeCallback, this));
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

void Connection::setProcessMessageCallback (std::function<void(Connection*, std::string)> fn) {process_message_callback_ = fn;}

void Connection::setSendCompleteCallback (std::function<void(Connection*)> fn) {send_complete_callback_ = fn;}

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
            // std::cout << "Receive \"" << input_buffer_.data() << "\" from " << fd() << std::endl;
            while(true) {
                int len;

                std::memcpy(&len, input_buffer_.data(), 4);
                if (input_buffer_.size() < len + 4) break;
                std::string message(input_buffer_.data() + 4, len);
                input_buffer_.erase(0, len + 4);
                std::cout << "Receive \"" << message << "\" from " << fd() << std::endl;

                process_message_callback_(this, message);
            }
            break;
        } else if (readn == 0) {
            closeCallback(); break;
        }
    }
}

void Connection::send(const char* data, size_t size) {
    output_buffer_.append(data, size);
    client_channel_->enableWriting();
}

void Connection::writeCallback() {
    ssize_t writen {::send(fd(), output_buffer_.data(), output_buffer_.size(), 0)};
    if (writen > 0) output_buffer_.erase(0, writen);
    if (output_buffer_.size() == 0) {
        client_channel_->disableWriting();
        send_complete_callback_(this);
    }
}
