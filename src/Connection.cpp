#include "Connection.h"

Connection::Connection(EventLoop* loop, Socket* client_socket) 
    :loop_(loop), client_socket_(client_socket), 
    client_channel_(new Channel(loop_, client_socket_->fd())), disconnect_(false) {
    client_channel_->setReadCallback(std::bind(&Connection::onMessage, this));
    client_channel_->setCloseCallback(std::bind(&Connection::closeCallback, this));
    client_channel_->setErrorCallback(std::bind(&Connection::errorCallback, this));
    client_channel_->setWriteCallback(std::bind(&Connection::writeCallback, this));
    client_channel_->enableEdgeTrigger();
    client_channel_->enableReading();
}

Connection::~Connection() {
    delete client_socket_;
}

int Connection::fd() const {return client_socket_->fd();}

std::string Connection::ip() const {return client_socket_->ip();}

uint16_t Connection::port() const {return client_socket_->port();}

void Connection::closeCallback() {disconnect_ = true; client_channel_->remove(); close_callback_(shared_from_this());}

void Connection::errorCallback() {disconnect_ = true; client_channel_->remove(); error_callback_(shared_from_this());}

void Connection::setCloseCallback(std::function<void(spConnection)> fn) {close_callback_ = fn;}

void Connection::setErrorCallback(std::function<void(spConnection)> fn) {error_callback_ = fn;}

void Connection::setProcessMessageCallback (std::function<void(spConnection, std::string&)> fn) {
    process_message_callback_ = fn;
}

void Connection::setSendCompleteCallback (std::function<void(spConnection)> fn) {send_complete_callback_ = fn;}

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

                process_message_callback_(shared_from_this(), message);
            }
            break;
        } else if (readn == 0) {
            closeCallback(); break;
        }
    }
}

void Connection::send(const char* data, size_t size) {
    if (disconnect_ == true) {printf("Client disconect, send() returned.\n"); return;}
    std::shared_ptr<std::string> message(new std::string(data));
    if (loop_->isInLoopThread()) {
        printf("send() is in EventLoop thread.\n");
        sendPlus(message);
    } else {
        printf("send() is not in EventLoop thread.\n");
        loop_->queueInLoop(std::bind(&Connection::sendPlus, this, message));
    }
}

void Connection::sendPlus(std::shared_ptr<std::string> data) {
    output_buffer_.appendWithHead(data->data(), data->size());
    client_channel_->enableWriting();
}

void Connection::writeCallback() {
    ssize_t writen {::send(fd(), output_buffer_.data(), output_buffer_.size(), 0)};
    if (writen > 0) output_buffer_.erase(0, writen);
    if (output_buffer_.size() == 0) {
        client_channel_->disableWriting();
        send_complete_callback_(shared_from_this());
    }
}
