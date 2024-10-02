#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    if (argc != 3) {std::cerr << "Usage: ./client <server_ip> <server_port>" << std::endl; return -1;}

    int client_fd {socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)};
    if (client_fd == -1) {perror("socket() failed"); return -1;}

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    server_address.sin_port = htons(atoi(argv[2]));
    if (connect(client_fd, reinterpret_cast<struct sockaddr*>(&server_address), sizeof(server_address)) == -1) {
        std::perror("connect() failed"); close(client_fd); return -1;
    }
    std::cout << "Connect OK" << std::endl;

    char buffer[1024];
    for (int i {0}; i < 1; ++i) {
        std::memset(buffer, 0, sizeof(buffer));
        std::snprintf(buffer, sizeof(buffer), "This is No.%d supergirl", i);

        char temp[1024];
        std::memset(temp, 0, sizeof(buffer));

        int len {static_cast<int>(std::strlen(buffer))};
        std::memcpy(temp, &len, 4);
        std::memcpy(temp + 4, buffer, len);

        if (send(client_fd, temp, len + 4, 0) == -1) {
            std::perror("send() failed"); close(client_fd); return -1;
        }
    }

    for (int i {0}; i < 1; ++i) {

        int len;
        recv(client_fd, &len, 4, 0);
        memset(buffer, 0, sizeof(buffer));
        if (recv(client_fd, buffer, len, 0) == -1) {
            std::cerr << "recv() failed" << std::endl; close(client_fd); return -1;
        }

        std::cout << "Received message: " << buffer << std::endl;
    }

    sleep(100);
}
