#include "EchoServer.h"

EchoServer::EchoServer(const char* ip, uint16_t port, int num_threads) : tcp_server_(ip, port, num_threads){
    tcp_server_.setNewConnectionCallback(std::bind(&EchoServer::handleNewConnection, this, std::placeholders::_1));
    tcp_server_.setCloseConnectionCallback(std::bind(&EchoServer::handleCloseConnection, this, std::placeholders::_1));
    tcp_server_.setErrorConnectionCallback(std::bind(&EchoServer::handleErrorConnection, this, std::placeholders::_1));
    tcp_server_.setProcessMessageCallback(std::bind(&EchoServer::handleProcessMessage, this, std::placeholders::_1, std::placeholders::_2));
    tcp_server_.setSendCompleteCallback(std::bind(&EchoServer::handleSendComplete, this, std::placeholders::_1));
    tcp_server_.setEpollTimeoutCallback(std::bind(&EchoServer::handleEpollTimeout, this, std::placeholders::_1));
}

EchoServer::~EchoServer() {}

void EchoServer::lanch() {tcp_server_.start();}

void EchoServer::handleNewConnection(Connection* conn) {
    std::cout << "Establish connection with <" << conn->ip() 
        << "> on <" << conn->port() << "> using <" << conn->fd() << ">" << std::endl;
    std::cout << "The main thread is " << syscall(SYS_gettid) << std::endl;
}

void EchoServer::handleCloseConnection(Connection* conn) {
    std::cerr << "Client @ " << conn->fd() << " disconnect." << std::endl;
}

void EchoServer::handleErrorConnection(Connection* conn) {
    std::cerr << "Client # " << conn->fd() << " disconnect." << std::endl;
}

void EchoServer::handleProcessMessage(Connection* conn, std::string& message) {
    std::cout << "The sub thread is " << syscall(SYS_gettid) << std::endl;
    message = "reply + " + message;
    conn->send(message.data(), message.size());
}

void EchoServer::handleSendComplete(Connection* conn) {
    std::cout << "All things were sent." << std::endl;
}

void EchoServer::handleEpollTimeout(EventLoop* loop) {
    std::cerr << "epoll_wait() time out." << std::endl;
}
