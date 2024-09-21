#ifndef INET_ADDRESS_H
#define INET_ADDRESS_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <cstdint>


class InetAddress {
private:
    struct sockaddr_in address_;

public:
    InetAddress(const char* ip, uint16_t port);    // For bind();

    InetAddress(const sockaddr_in address);               // For accept();

    ~InetAddress();

    const struct sockaddr* addr() const;

    const char* ip() const;

    uint16_t port() const;
};

#endif
