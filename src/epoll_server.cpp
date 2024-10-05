#include "EchoServer.h"
#include <signal.h>

EchoServer* echo_server;

void truelyStop(int sig) {
    printf("sig = %d.\n", sig);
    echo_server->serverStop();
    printf("echo_server is killed.\n");
    delete echo_server;
    exit(0);
}

int main(int argc, char* argv[]) {
    // Prompt for usage.
    if (argc != 3) {
        std::cerr << "Usage: ./server <server_ip> <server_port>" << std::endl;
        std::cerr << "Example: ./server 127.0.0.1 5099" << std::endl;
        return -1;
    }

    signal(SIGINT, truelyStop);
    signal(SIGTERM, truelyStop);

    echo_server = new EchoServer(argv[1], atoi(argv[2]), 3, 2); 
    echo_server->lanch();

    return 0;
}
