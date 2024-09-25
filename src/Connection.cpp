#include "Connection.h"

Connection::Connection(EventLoop* loop, Socket* client_socket) : loop_(loop), client_socket_(client_socket) {
    client_channel_ = new Channel(loop_, client_socket_->fd());
    client_channel_->setReadCallback(std::bind(&Channel::onMessage, client_channel_));
    client_channel_->enableEdgeTrigger();
    client_channel_->enableReading();
}

Connection::~Connection() {
    delete client_socket_;
    delete client_channel_;
}
