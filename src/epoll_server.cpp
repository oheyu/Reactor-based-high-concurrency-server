#include "TcpServer.h"

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
