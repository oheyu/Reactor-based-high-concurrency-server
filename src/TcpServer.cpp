#include "TcpServer.h"


TcpServer::TcpServer(const char* ip, uint16_t port) {
    acceptor_ = new Acceptor(&loop_, ip, port);
    acceptor_->setNewConnection(std::bind(&TcpServer::newConnection, this, std::placeholders::_1));
}

TcpServer::~TcpServer() {
    delete acceptor_;
}

void TcpServer::start() {loop_.run();}

void TcpServer::newConnection(Socket* client_socket) {
    Connection* connection {new Connection(&loop_, client_socket)};
}
