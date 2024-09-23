#include "InetAddress.h"
#include "Socket.h"
#include "Epoll.h"
#include "Channel.h"

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

    Epoll epoll_sniper;
    Channel* server_channel {new Channel(&epoll_sniper, server_socket.fd(), true)};
    server_channel->enableReading();

    while (true) {
        std::vector<Channel*> results {epoll_sniper.loop()};

        for (auto& result : results) {result->handleEvent(&server_socket);}
    }

    return 0;
}
