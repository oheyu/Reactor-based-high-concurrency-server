#include <iostream>
#include <sys/socket.h>
#include <cstring>
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
        perror("connect() failed"); close(client_fd); return -1;
    }
    std::cout << "Connect OK" << std::endl;

    char buffer[1024];
    while (true) {
        std::cout << "Please enter message you want to send (enter 'quit' to stop): ";
        memset(buffer, 0, sizeof(buffer));
        std::cin.get(buffer, sizeof(buffer)).get();
        if (strcmp(buffer, "quit") == 0) {close(client_fd); return 0;}

        if (send(client_fd, buffer, strlen(buffer), 0) == -1) {
            perror("send() failed"); close(client_fd); return -1;
        }

        memset(buffer, 0, sizeof(buffer));
        if (recv(client_fd, buffer, sizeof(buffer), 0) == -1) {
            std::cerr << "recv() failed" << std::endl; close(client_fd); return -1;
        }

        std::cout << "Received message: " << buffer << std::endl;
    }
}
