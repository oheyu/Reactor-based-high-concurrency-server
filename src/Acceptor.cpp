#include "Acceptor.h"

Acceptor::Acceptor(EventLoop* loop, const char* ip, uint16_t port) : loop_(loop) {
    server_socket_ = new Socket(createNonBlock());
    server_socket_->setReuseAddr(true);
    server_socket_->setReusePort(true);
    server_socket_->setTcpNoDelay(true);
    server_socket_->setKeepAlive(true);

    InetAddress server_address(ip, port);
    server_socket_->bind(server_address);
    server_socket_->listen();

    accept_channel_ = new Channel(loop_, server_socket_->fd());
    accept_channel_->setReadCallback(std::bind(&Acceptor::newConnection, this));
    accept_channel_->enableReading();
}

Acceptor::~Acceptor() {
    delete server_socket_;
    delete accept_channel_;
}

void Acceptor::newConnection() {
    InetAddress client_address;
    Socket* client_socket {new Socket(server_socket_->accept(client_address))};
    if (client_socket->fd() == -1) {
        std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__
            << "-> connection error: " << std::strerror(errno) << std::endl;
        exit(-1);
    }
    
    new_connection_(client_socket);
}

void Acceptor::setNewConnection(std::function<void(Socket*)> fn) {
    new_connection_ = fn;
}
