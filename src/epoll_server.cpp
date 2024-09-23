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
    Channel* server_channel {new Channel(&epoll_sniper, server_socket.fd())};
    server_channel->enableReading();

    while (true) {
        std::vector<Channel*> results {epoll_sniper.loop()};

        for (auto& result : results) {
            if (result->revents() & EPOLLRDHUP) {
                std::cerr << "Client @ " << result->fd() << " disconnect." << std::endl;
                close(result->fd()); continue;
            } else if (result->revents() & (EPOLLIN | EPOLLPRI)) {
                if (result->fd() == server_socket.fd()) {
                    InetAddress client_address;
                    Socket* client_socket {new Socket(server_socket.accept(client_address))};
                    if (client_socket->fd() == -1) {
                        std::cerr << __FILE__ << " # " << __FUNCTION__ << " # " << __LINE__
                            << "-> connection error: " << std::strerror(errno) << std::endl;
                        break;
                    }
                    std::cout << "Establish connection with <" << client_address.ip() 
                        << "> on <" << client_address.port() << "> using <" << client_socket->fd() << ">" << std::endl;

                    Channel* client_channel {new Channel(&epoll_sniper, client_socket->fd())};
                    client_channel->enableEdgeTrigger();
                    client_channel->enableReading();
                } else {
                    char buffer[1024];
                    while (true) {
                        bzero(buffer, sizeof(buffer));
                        ssize_t readn {recv(result->fd(), buffer, sizeof(buffer), 0)};
                        if (readn > 0) {
                            std::string message(buffer);
                            std::cout << "Receive \"" << message << "\" from " << result->fd() << std::endl;
                            send(result->fd(), buffer, sizeof(buffer), 0);
                        } else if (readn == -1 && errno == EINTR) {       // Interrupt.
                            continue;
                        } else if (readn == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) {        // No data.
                            break;
                        } else if (readn == 0) {
                            std::cerr << "Client # " << result->fd() << " disconnect." << std::endl;
                            close(result->fd()); break;
                        }
                    }
                }
            } else if (result->fd() & EPOLLOUT) {
                // Accomplish later.
            } else {
                std::cerr << "Error on " << result->fd() << " anyway" << std::endl;
                close(result->fd());
            }
        }
    }

    return 0;
}
