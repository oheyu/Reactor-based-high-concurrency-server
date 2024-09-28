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
    Connection* conn {new Connection(&loop_, client_socket)};

    conn->setCloseCallback(std::bind(&TcpServer::closeConnection, this, std::placeholders::_1));
    conn->setErrorCallback(std::bind(&TcpServer::errorConnection, this, std::placeholders::_1));
    conn->setProcessMessageCallback(std::bind(&TcpServer::processMessage, this, std::placeholders::_1, std::placeholders::_2));

    std::cout << "Establish connection with <" << conn->ip() 
        << "> on <" << conn->port() << "> using <" << conn->fd() << ">" << std::endl;

    connections_[conn->fd()] = conn;
}

void TcpServer::closeConnection(Connection* conn) {
    std::cerr << "Client @ " << conn->fd() << " disconnect." << std::endl;
    connections_.erase(conn->fd());
    delete conn;
}

void TcpServer::errorConnection(Connection* conn) {
    std::cerr << "Client # " << conn->fd() << " disconnect." << std::endl;
    connections_.erase(conn->fd());
    delete conn;
}

void TcpServer::processMessage(Connection* conn, std::string message) {
    message = "reply + " + message;
    int len = static_cast<int>(message.size());
    std::string temp((char*)&len, 4);
    temp.append(message);
    conn->send(temp.data(), temp.size());
}
