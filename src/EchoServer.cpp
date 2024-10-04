#include "EchoServer.h"

EchoServer::EchoServer(const char* ip, uint16_t port, int io_threads, int work_threads) : 
    tcp_server_(ip, port, io_threads), thread_pool_(work_threads, "WORKS"){
    tcp_server_.setNewConnectionCallback(std::bind(&EchoServer::handleNewConnection, this, std::placeholders::_1));
    tcp_server_.setCloseConnectionCallback(std::bind(&EchoServer::handleCloseConnection, this, std::placeholders::_1));
    tcp_server_.setErrorConnectionCallback(std::bind(&EchoServer::handleErrorConnection, this, std::placeholders::_1));
    tcp_server_.setProcessMessageCallback(std::bind(&EchoServer::handleProcessMessage, this, 
                std::placeholders::_1, std::placeholders::_2));
    tcp_server_.setSendCompleteCallback(std::bind(&EchoServer::handleSendComplete, this, std::placeholders::_1));
    tcp_server_.setEpollTimeoutCallback(std::bind(&EchoServer::handleEpollTimeout, this, std::placeholders::_1));
}

EchoServer::~EchoServer() {}

void EchoServer::lanch() {tcp_server_.start();}

void EchoServer::handleNewConnection(spConnection conn) {
    std::cout << "Establish connection with <" << conn->ip() 
        << "> on <" << conn->port() << "> using <" << conn->fd() << ">" << std::endl;
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
}

void EchoServer::handleCloseConnection(spConnection conn) {
    std::cerr << "Client @ " << conn->fd() << " disconnect." << std::endl;
}

void EchoServer::handleErrorConnection(spConnection conn) {
    std::cerr << "Client # " << conn->fd() << " disconnect." << std::endl;
}

void EchoServer::handleProcessMessage(spConnection conn, std::string& message) {
    if (thread_pool_.size() == 0) {
        onMessage(conn, message);
    } else {
        thread_pool_.addTask(std::bind(&EchoServer::onMessage, this, conn, message));
    }
}

void EchoServer::onMessage(spConnection conn, std::string& message) {
    message = "reply + " + message;
    conn->send(message.data(), message.size());
}

void EchoServer::handleSendComplete(spConnection conn) {
    std::cout << "All things were sent." << std::endl;
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
}

void EchoServer::handleEpollTimeout(EventLoop* loop) {
    std::cerr << "epoll_wait() time out." << std::endl;
}
