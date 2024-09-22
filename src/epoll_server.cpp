#include "InetAddress.h"
#include "Socket.h"
#include "Epoll.h"

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

    // int epoll_fd {epoll_create(1)};

    // struct epoll_event interest_event;
    // interest_event.data.fd = server_socket.getFd();
    // interest_event.events = EPOLLIN;       // Adopt default LT.

    // epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket.getFd(), &interest_event);

    // struct epoll_event results[10];        // Store results returned by epoll_wait();

    Epoll epoll_sniper;
    epoll_sniper.collectInterests(server_socket.getFd(), EPOLLIN);
    std::vector<epoll_event> results;

    while (true) {
        // int in_fd {epoll_wait(epoll_fd, results, 10, -1)};

        // if (in_fd == -1) {perror("epoll_wait() failed"); break;}
        // if (in_fd == 0) {std::cerr << "time out" << std::endl; continue;}
        results = epoll_sniper.loop();

        for (auto& result : results) {
            if (result.events & EPOLLRDHUP) {
                std::cerr << "Client @ " << result.data.fd << " disconnect." << std::endl;
                close(result.data.fd); continue;
            } else if (result.events & (EPOLLIN | EPOLLPRI)) {
                if (result.data.fd == server_socket.getFd()) {
                    InetAddress client_address;
                    Socket* client_socket {new Socket(server_socket.accept(client_address))};
                    if (client_socket->getFd() == -1) {
                        std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__
                            << "-> connection error: " << std::strerror(errno) << std::endl;
                        break;
                    }
                    std::cout << "Establish connection with <" << client_address.ip() 
                        << "> on <" << client_address.port() << "> using <" << client_socket->getFd() << ">" << std::endl;

                    // interest_event.data.fd = client_socket->getFd();
                    // interest_event.events = EPOLLIN;
                    // epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket->getFd(), &interest_event);
                    epoll_sniper.collectInterests(client_socket->getFd(), EPOLLIN|EPOLLIN);
                } else {
                    char buffer[1024];
                    while (true) {
                        bzero(buffer, sizeof(buffer));
                        ssize_t readn {recv(result.data.fd, buffer, sizeof(buffer), 0)};
                        if (readn > 0) {
                            std::string message(buffer);
                            std::cout << "Receive \"" << message << "\" from " << result.data.fd << std::endl;
                            send(result.data.fd, buffer, sizeof(buffer), 0);
                        } else if (readn == -1 && errno == EINTR) {       // Interrupt.
                            continue;
                        } else if (readn == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) {        // No data.
                            break;
                        } else if (readn == 0) {
                            std::cerr << "Client # " << result.data.fd << " disconnect." << std::endl;
                            close(result.data.fd); break;
                        }
                    }
                }
            } else if (result.data.fd & EPOLLOUT) {
                // Accomplish later.
            } else {
                std::cerr << "Error on " << result.data.fd << " anyway" << std::endl;
                close(result.data.fd);
            }
        }
    }

    return 0;
}
