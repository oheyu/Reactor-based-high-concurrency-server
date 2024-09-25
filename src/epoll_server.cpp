#include "InetAddress.h"
#include "Socket.h"
#include "Epoll.h"
#include "Channel.h"
#include "EventLoop.h"

#include <iostream>
#include <fcntl.h>
#include <sys/socket.h>
#include <cstring>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/epoll.h>


int main(int argc, char* argv[]) {
    // Prompt for usage.
    if (argc != 3) {
        std::cerr << "Usage: ./server <server_ip> <server_port>" << std::endl;
        std::cerr << "Example: ./server 127.0.0.1 5099" << std::endl;
        return -1;
    }

    Socket server_socket(createNonBlock());
    server_socket.setReuseAddr(true);
    server_socket.setReusePort(true);
    server_socket.setTcpNoDelay(true);
    server_socket.setKeepAlive(true);

    InetAddress server_address(argv[1], atoi(argv[2]));
    server_socket.bind(server_address);
    server_socket.listen();

    EventLoop loop;
    Channel* server_channel {new Channel(&loop, server_socket.fd())};
    server_channel->setReadCallback(std::bind(&Channel::newConnection, server_channel, &server_socket));
    server_channel->enableReading();

    loop.run();

    return 0;
}
