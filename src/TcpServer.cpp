#include "TcpServer.h"


TcpServer::TcpServer(const char* ip, uint16_t port) {
    Socket* server_socket {new Socket(createNonBlock())};
    server_socket->setReuseAddr(true);
    server_socket->setReusePort(true);
    server_socket->setTcpNoDelay(true);
    server_socket->setKeepAlive(true);

    InetAddress server_address(ip, port);
    server_socket->bind(server_address);
    server_socket->listen();

    Channel* server_channel {new Channel(&loop_, server_socket->fd())};
    server_channel->setReadCallback(std::bind(&Channel::newConnection, server_channel, server_socket));
    server_channel->enableReading();
}

TcpServer::~TcpServer() {}

void TcpServer::start() {loop_.run();}
