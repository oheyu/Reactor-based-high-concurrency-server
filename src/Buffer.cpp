#include "Buffer.h"

Buffer::Buffer(uint16_t seperation) : seperation_(seperation) {}

Buffer::~Buffer() {}

void Buffer::append(const char* data, size_t size) {buffer_.append(data, size);}

void Buffer::appendWithSeperation(const char* data, size_t size) {
    if (seperation_ == 0) {
        buffer_.append(data, size);
    } else if (seperation_ == 1) {
        buffer_.append((char*)&size, 4);
        buffer_.append(data, size);
    } else {
        // Write your code here.
    }
}

void Buffer::erase(size_t pos, size_t n) {buffer_.erase(pos, n);}

size_t Buffer::size() {return buffer_.size();}

const char* Buffer::data() {return buffer_.data();}

void Buffer::clear() {buffer_.clear();}

bool Buffer::pickMessage(std::string& ss) {
    if (buffer_.empty()) return false;

    if (seperation_ == 0) {
        ss = buffer_;
        buffer_.clear();
    } else if (seperation_ == 1) {
        int len;

        std::memcpy(&len, buffer_.data(), 4);
        if (buffer_.size() < len + 4) return false;
        ss = buffer_.substr(4, len);
        buffer_.erase(0, len + 4);
    } else {
        // Write your code here.
    }
    return true;
}
