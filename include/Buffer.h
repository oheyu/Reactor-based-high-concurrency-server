#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <string>

class Buffer {
private:
    std::string buffer_;

public:
    Buffer();

    ~Buffer();

    void append(const char* data, size_t size);

    void erase(size_t pos, size_t n);

    size_t size();

    const char* data();

    void clear();
};

#endif // !BUFFER_H
