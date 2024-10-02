#include "Buffer.h"

Buffer::Buffer() {}

Buffer::~Buffer() {}

void Buffer::append(const char* data, size_t size) {buffer_.append(data, size);}

void Buffer::appendWithHead(const char* data, size_t size) {
    buffer_.append((char*)&size, 4);
    buffer_.append(data, size);
}

void Buffer::erase(size_t pos, size_t n) {buffer_.erase(pos, n);}

size_t Buffer::size() {return buffer_.size();}

const char* Buffer::data() {return buffer_.data();}

void Buffer::clear() {buffer_.clear();}
