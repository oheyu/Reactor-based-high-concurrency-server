#include "InetAddress.h"
#include "Socket.h"
#include "Epoll.h"
#include "Channel.h"
#include "EventLoop.h"
#include "TcpServer.h"

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

    TcpServer tcp_server(argv[1], atoi(argv[2]));

    tcp_server.start();

    return 0;
}
