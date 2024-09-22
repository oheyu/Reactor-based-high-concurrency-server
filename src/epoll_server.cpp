#include "InetAddress.h"
#include "Socket.h"

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

    Socket listen_fd(createNonBlock());
    listen_fd.setReuseAddr(true);
    listen_fd.setReusePort(true);
    listen_fd.setTcpNoDelay(true);
    listen_fd.setKeepAlive(true);

    InetAddress server_address(argv[1], atoi(argv[2]));
    listen_fd.bind(server_address);
    listen_fd.listen();

    int epoll_fd {epoll_create(1)};

    struct epoll_event interest_event;
    interest_event.data.fd = listen_fd.getFd();
    interest_event.events = EPOLLIN;       // Adopt default LT.

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd.getFd(), &interest_event);

    struct epoll_event results[10];        // Store results returned by epoll_wait();

    while (true) {
        int in_fd {epoll_wait(epoll_fd, results, 10, -1)};

        if (in_fd == -1) {perror("epoll_wait() failed"); break;}
        if (in_fd == 0) {std::cerr << "time out" << std::endl; continue;}

        for (int i {0}; i < in_fd; ++i) {
            if (results[i].events & EPOLLRDHUP) {
                std::cerr << "Client @ " << results[i].data.fd << " disconnect." << std::endl;
                close(results[i].data.fd); continue;
            } else if (results[i].events & (EPOLLIN | EPOLLPRI)) {
                if (results[i].data.fd == listen_fd.getFd()) {
                    // struct sockaddr_in peer_address;
                    // socklen_t length {static_cast<socklen_t>(sizeof(peer_address))};
                    // int client_fd {accept4(listen_fd.getFd(), (struct sockaddr*)(&peer_address), &length, SOCK_NONBLOCK)};
                    InetAddress client_address;
                    Socket* client_fd {new Socket(listen_fd.accept(client_address))};
                    if (client_fd->getFd() == -1) {
                        std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__
                            << "-> bind socket error: " << std::strerror(errno) << std::endl;
                        break;
                    }
                    std::cout << "Establish connection with <" << client_address.ip() 
                        << "> on <" << client_address.port() << "> using <" << client_fd->getFd() << ">" << std::endl;

                    interest_event.data.fd = client_fd->getFd();
                    interest_event.events = EPOLLIN;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd->getFd(), &interest_event);
                } else {
                    char buffer[1024];
                    while (true) {
                        bzero(buffer, sizeof(buffer));
                        ssize_t readn {recv(results[i].data.fd, buffer, sizeof(buffer), 0)};
                        if (readn > 0) {
                            std::string message(buffer);
                            std::cout << "Receive \"" << message << "\" from " << results[i].data.fd << std::endl;
                            send(results[i].data.fd, buffer, sizeof(buffer), 0);
                        } else if (readn == -1 && errno == EINTR) {       // Interrupt.
                            continue;
                        } else if (readn == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) {        // No data.
                            break;
                        } else if (readn == 0) {
                            std::cerr << "Client # " << results[i].data.fd << " disconnect." << std::endl;
                            close(results[i].data.fd); break;
                        }
                    }
                }
            } else if (results[i].data.fd & EPOLLOUT) {
                // Accomplish later.
            } else {
                std::cerr << "Error on " << results[i].data.fd << " anyway" << std::endl;
                close(results[i].data.fd);
            }
        }
    }

    return 0;
}
