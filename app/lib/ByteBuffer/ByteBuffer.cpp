/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** ByteBuffer RTYPE
*/

#include "lib/ByteBuffer/ByteBuffer.hpp"

ByteBuffer::ByteBuffer(size_t _capacity) : capacity(_capacity)
{
    this->capacity = _capacity;
    this->offset = 0;
    this->buf = new unsigned char[_capacity];
    std::memset(this->buf, 0, this->capacity);
}

ByteBuffer::ByteBuffer(const char *buf)
{
    this->capacity = std::strlen(buf) + 1;
    this->offset = 0;
    this->buf = new unsigned char[this->capacity];
    std::memcpy(this->buf, buf, std::strlen(buf)+1);
}

ByteBuffer::~ByteBuffer()
{
    delete [] this->buf;
}

void ByteBuffer::clear() {
    if (this->size > 0) {
        std::memset(this->buf, 0, this->capacity);
        this->size = 0;
    }
    this->offset = 0;
}

size_t ByteBuffer::eat() {
    size_t len = offset;
    if (len > 0) {
        std::memmove(this->buf, this->buf + offset, this->size - this->offset);
        this->size -= this->offset;
        this->offset = 0;
    }
    return len;
}

size_t ByteBuffer::read(char *buf, size_t size) {
    size_t move = std::min(size, this->size - this->offset);
    std::memcpy(buf, this->buf + offset, move);
    this->offset += move;
    this->eat();
    return move;
}

size_t ByteBuffer::read(ByteBuffer &buf, size_t size) {
    size_t move = std::min(size, this->size - this->offset);
    buf.append(reinterpret_cast<char *>(this->buf) + offset, move);
    this->offset += move;
    this->eat();
    return move;
}

size_t ByteBuffer::append(const char *buf, size_t bufLen) {
    reserveSize(bufLen);
    std::memcpy(this->buf + this->size, buf, bufLen);
    this->size += bufLen;
    return bufLen;
}

const unsigned char *ByteBuffer::flush() const {
    return this->buf;
}

size_t ByteBuffer::getSize() const {
    return this->size;
}

size_t ByteBuffer::getCapacity() const {
    return this->capacity;
}

int ByteBuffer::seek(size_t pos, bool fromEnd) {
    if (pos > this->size)
        return -1;
    this->offset = fromEnd ? this->size - pos : pos;
    return this->offset;
}

void ByteBuffer::shrink() {
    unsigned char *buf = new unsigned char[this->size];
    std::memcpy(buf, this->buf, this->size);
    delete [] this->buf;
    this->buf = buf;
    this->capacity = this->size;
}

void ByteBuffer::grow(size_t _capacity) {
    unsigned char *buf = new unsigned char[this->capacity + _capacity];
    std::memset(buf, 0, this->capacity + _capacity);
    std::memcpy(buf, this->buf, this->size);
    delete [] this->buf;
    this->buf = buf;
    this->capacity += _capacity;
}

void ByteBuffer::reserveSize(size_t size) {
    if (this->size + size <= this->capacity)
        return;
    this->grow(std::max(this->capacity >> 1, size));
}

void ByteBuffer::writeBool(bool value) {
    this->reserveSize(1);
    this->buf[this->size] = value;
    this->size += 1;
}

void ByteBuffer::writeChar(char value) {
    this->reserveSize(1);
    this->buf[this->size] = static_cast<unsigned char>(value);
    this->size += 1;
}

void ByteBuffer::writeUChar(unsigned char value) {
    this->reserveSize(1);
    this->buf[this->size] = value;
    this->size += 1;
}

void ByteBuffer::writeShort(short value) {
    this->reserveSize(2);
    this->buf[this->size] = value & 0xFF;
    this->buf[this->size + 1] = (value >> 8) & 0xFF;
    this->size += 2;
}

void ByteBuffer::writeUShort(unsigned short value) {
    this->reserveSize(2);
    this->buf[this->size] = value & 0xFF;
    this->buf[this->size + 1] = (value >> 8) & 0xFF;
    this->size += 2;
}

void ByteBuffer::writeInt(int value) {
    this->reserveSize(4);
    this->buf[this->size] = value & 0xFF;
    this->buf[this->size + 1] = (value >> 8) & 0xFF;
    this->buf[this->size + 2] = (value >> 16) & 0xFF;
    this->buf[this->size + 3] = (value >> 24) & 0xFF;
    this->size += 4;
}

void ByteBuffer::writeUInt(unsigned int value) {
    this->reserveSize(4);
    this->buf[this->size] = value & 0xFF;
    this->buf[this->size + 1] = (value >> 8) & 0xFF;
    this->buf[this->size + 2] = (value >> 16) & 0xFF;
    this->buf[this->size + 3] = (value >> 24) & 0xFF;
    this->size += 4;
}

void ByteBuffer::writeLong(long value) {
    this->reserveSize(8);
    this->buf[this->size] = value & 0xFF;
    this->buf[this->size + 1] = (value >> 8) & 0xFF;
    this->buf[this->size + 2] = (value >> 16) & 0xFF;
    this->buf[this->size + 3] = (value >> 24) & 0xFF;
    this->buf[this->size + 4] = (value >> 32) & 0xFF;
    this->buf[this->size + 5] = (value >> 40) & 0xFF;
    this->buf[this->size + 6] = (value >> 48) & 0xFF;
    this->buf[this->size + 7] = (value >> 56) & 0xFF;
    this->size += 8;
}

void ByteBuffer::writeULong(unsigned long value) {
    this->reserveSize(8);
    this->buf[this->size] = value & 0xFF;
    this->buf[this->size + 1] = (value >> 8) & 0xFF;
    this->buf[this->size + 2] = (value >> 16) & 0xFF;
    this->buf[this->size + 3] = (value >> 24) & 0xFF;
    this->buf[this->size + 4] = (value >> 32) & 0xFF;
    this->buf[this->size + 5] = (value >> 40) & 0xFF;
    this->buf[this->size + 6] = (value >> 48) & 0xFF;
    this->buf[this->size + 7] = (value >> 56) & 0xFF;
    this->size += 8;
}

void ByteBuffer::writeFloat(float value) {
    FloatValue partedValue;
    partedValue.floatPart = value;
    this->writeUInt(partedValue.intPart);
}

void ByteBuffer::writeDouble(double value) {
    DoubleValue partedValue;
    partedValue.doublePart = value;
    this->writeULong(partedValue.longPart);
}

void ByteBuffer::writeString(const std::string &str, int size) {
    this->writeCharBuffer(str.c_str(), size);
}

void ByteBuffer::writeCharBuffer(const char *buf, int size) {
    int length = size == -1 ? std::strlen(buf) + 1 : size;
    this->reserveSize(length + 4);
    this->writeUInt(length);
    std::memcpy(this->buf + this->size, buf, length);
    this->size += length;
}

bool ByteBuffer::readBool(int *err) {
    if (this->offset + 1 > this->size) {
        if (err != nullptr)
            *err = 1;
        return false;
    }
    bool value = buf[offset] == 1;
    offset += 1;
    return value;
}

char ByteBuffer::readChar(int *err) {
    if (this->offset + 1 > this->size) {
        if (err != nullptr)
            *err = 1;
        return 0;
    }
    unsigned char value = buf[offset];
    offset += 1;
    return static_cast<char>(value);
}

unsigned char ByteBuffer::readUChar(int *err) {
    if (this->offset + 1 > this->size) {
        if (err != nullptr)
            *err = 1;
        return 0;
    }
    unsigned char value = buf[offset];
    offset += 1;
    return value;
}

short ByteBuffer::readShort(int *err) {
    if (this->offset + 2 > this->size) {
        if (err != nullptr)
            *err = 1;
        return 0;
    }
    short value = buf[offset];
    value |= buf[offset + 1] << 8;
    offset += 2;
    return value;
}

unsigned short ByteBuffer::readUShort(int *err) {
    if (this->offset + 2 > this->size) {
        if (err != nullptr)
            *err = 1;
        return 0;
    }
    unsigned short value = buf[offset];
    value |= buf[offset + 1] << 8;
    offset += 2;
    return value;
}

int ByteBuffer::readInt(int *err) {
    if (this->offset + 4 > this->size) {
        if (err != nullptr)
            *err = 1;
        return 0;
    }
    int value = buf[offset];
    value |= buf[offset + 1] << 8;
    value |= buf[offset + 2] << 16;
    value |= buf[offset + 3] << 24;
    offset += 4;
    return value;
}

unsigned int ByteBuffer::readUInt(int *err) {
    if (this->offset + 4 > this->size) {
        if (err != nullptr)
            *err = 1;
        return 0;
    }
    unsigned int value = buf[offset];
    value |= buf[offset + 1] << 8;
    value |= buf[offset + 2] << 16;
    value |= buf[offset + 3] << 24;
    offset += 4;
    return value;
}

long ByteBuffer::readLong(int *err) {
    if (this->offset + 8 > this->size) {
        if (err != nullptr)
            *err = 1;
        return 0;
    }
    long value = buf[offset];
    value |= static_cast<long>(buf[offset + 1]) << 8;
    value |= static_cast<long>(buf[offset + 2]) << 16;
    value |= static_cast<long>(buf[offset + 3]) << 24;
    value |= static_cast<long>(buf[offset + 4]) << 32;
    value |= static_cast<long>(buf[offset + 5]) << 40;
    value |= static_cast<long>(buf[offset + 6]) << 48;
    value |= static_cast<long>(buf[offset + 7]) << 56;
    offset += 8;
    return value;
}

unsigned long ByteBuffer::readULong(int *err) {
    if (this->offset + 8 > this->size) {
        if (err != nullptr)
            *err = 1;
        return 0;
    }
    long value = buf[offset];
    value |= static_cast<long>(buf[offset + 1]) << 8;
    value |= static_cast<long>(buf[offset + 2]) << 16;
    value |= static_cast<long>(buf[offset + 3]) << 24;
    value |= static_cast<long>(buf[offset + 4]) << 32;
    value |= static_cast<long>(buf[offset + 5]) << 40;
    value |= static_cast<long>(buf[offset + 6]) << 48;
    value |= static_cast<long>(buf[offset + 7]) << 56;
    offset += 8;
    return value;
}

float ByteBuffer::readFloat(int *err) {
    if (this->offset + 4 > this->size) {
        if (err != nullptr)
            *err = 1;
        return 0;
    }
    FloatValue value;
    value.intPart = buf[offset];
    value.intPart |= buf[offset + 1] << 8;
    value.intPart |= buf[offset + 2] << 16;
    value.intPart |= buf[offset + 3] << 24;
    offset += 4;
    return value.floatPart;
}

double ByteBuffer::readDouble(int *err) {
    if (this->offset + 8 > this->size) {
        if (err != nullptr)
            *err = 1;
        return 0;
    }
    DoubleValue value;
    value.longPart = buf[offset];
    value.longPart |= static_cast<long>(buf[offset + 1]) << 8;
    value.longPart |= static_cast<long>(buf[offset + 2]) << 16;
    value.longPart |= static_cast<long>(buf[offset + 3]) << 24;
    value.longPart |= static_cast<long>(buf[offset + 4]) << 32;
    value.longPart |= static_cast<long>(buf[offset + 5]) << 40;
    value.longPart |= static_cast<long>(buf[offset + 6]) << 48;
    value.longPart |= static_cast<long>(buf[offset + 7]) << 56;
    offset += 8;
    return value.doublePart;
}

char *ByteBuffer::readCharBuffer(int *err) {
    int cerr = 0;
    size_t size = readUInt(&cerr);
    if (cerr == 1) {
        if (err != nullptr)
            *err = 1;
        return nullptr;
    }
    if (this->offset + size > this->size) {
        if (err != nullptr)
            *err = 1;
        return nullptr;
    }
    char *str = new char[size];
    if (str == nullptr) {
        if (err != nullptr)
            *err = 1;
        return nullptr;
    }
    std::memcpy(str, this->buf + offset, size);
    offset += size;
    return str;
}

std::string *ByteBuffer::readString(int *err) {
    int cerr = 0;
    char *str = this->readCharBuffer(&cerr);
    if (cerr == 1 || str == nullptr) {
        if (err != nullptr)
            *err = 1;
        return nullptr;
    }
    std::string *nstr = new std::string(str);
    delete [] str;
    return nstr;
}