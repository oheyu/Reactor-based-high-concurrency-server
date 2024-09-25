#include "TcpServer.h"


TcpServer::TcpServer(const char* ip, uint16_t port) {
    acceptor_ = new Acceptor(&loop_, ip, port);
    acceptor_->setNewConnection(std::bind(&TcpServer::newConnection, this, std::placeholders::_1));
}

TcpServer::~TcpServer() {
    delete acceptor_;
    for (auto& temp : connections_) delete temp.second;
}

void TcpServer::start() {loop_.run();}

void TcpServer::newConnection(Socket* client_socket) {
    Connection* connection {new Connection(&loop_, client_socket)};

    connection->setCloseCallback(std::bind(&TcpServer::closeConnection, this, std::placeholders::_1));
    connection->setErrorCallback(std::bind(&TcpServer::errorConnection, this, std::placeholders::_1));

    std::cout << "Establish connection with <" << connection->ip() 
        << "> on <" << connection->port() << "> using <" << connection->fd() << ">" << std::endl;

    connections_[connection->fd()] = connection;
}

void TcpServer::closeConnection(Connection* connection) {
    std::cerr << "Client @ " << connection->fd() << " disconnect." << std::endl;
    connections_.erase(connection->fd());
    delete connection;
}

void TcpServer::errorConnection(Connection* connection) {
    std::cerr << "Client # " << connection->fd() << " disconnect." << std::endl;
    connections_.erase(connection->fd());
    delete connection;
}
