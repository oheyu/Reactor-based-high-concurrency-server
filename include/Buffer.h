#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>

class Buffer {
private:
    std::string buffer_;
    const uint16_t seperation_;

public:
    Buffer(uint16_t seperation = 1);

    ~Buffer();

    void append(const char* data, size_t size);

    void appendWithSeperation(const char* data, size_t size);

    void erase(size_t pos, size_t n);

    size_t size();

    const char* data();

    void clear();

    bool pickMessage(std::string& ss);
};

#endif // !BUFFER_H
