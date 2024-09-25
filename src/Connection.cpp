#include "Connection.h"

Connection::Connection(EventLoop* loop, Socket* client_socket) : loop_(loop), client_socket_(client_socket) {
    client_channel_ = new Channel(loop_, client_socket_->fd());
    client_channel_->setReadCallback(std::bind(&Channel::onMessage, client_channel_));
    client_channel_->setCloseCallback(std::bind(&Connection::closeCallBack, this));
    client_channel_->setErrorCallback(std::bind(&Connection::errorCallBack, this));
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

void Connection::closeCallBack() {close_callback_(this);}

void Connection::errorCallBack() {error_callback_(this);}

void Connection::setCloseCallback(std::function<void(Connection*)> fn) {close_callback_ = fn;}

void Connection::setErrorCallback(std::function<void(Connection*)> fn) {error_callback_ = fn;}
