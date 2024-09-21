#include "InetAddress.h"


InetAddress::InetAddress(const char* ip, uint16_t port) {
    address_.sin_family = AF_INET;
    address_.sin_addr.s_addr = inet_addr(ip);
    address_.sin_port = htons(port);
}

InetAddress::InetAddress(const sockaddr_in address) : address_(address) {}

InetAddress::~InetAddress() {}

const struct sockaddr* InetAddress::addr() const {
    return reinterpret_cast<const struct sockaddr*>(&address_);
}

const char* InetAddress::ip() const {
    return inet_ntoa(address_.sin_addr);
}

uint16_t InetAddress::port() const {
    return ntohs(address_.sin_port);
}
