/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** ByteBuffer RTYPE
*/

#ifndef BYTEBUFFER_HPP_
#define BYTEBUFFER_HPP_

#include <memory>
#include <iostream>
#include <string>
#include <cstring>

typedef union FloatValue {
    float floatPart;
    unsigned int intPart;
} FloatValue;

typedef union DoubleValue {
    double doublePart;
    unsigned long longPart;
} DoubleValue;

class ByteBuffer {
    public:
        ByteBuffer(size_t capacity);
        ByteBuffer(const char *buf);
        ~ByteBuffer();

        void clear();
        const unsigned char *flush() const;

        void shrink();
        void grow(size_t capacity);
        int seek(size_t pos, bool fromEnd = false);
        int move(int pos);

        size_t getCapacity() const;
        size_t getSize() const;

        size_t eat();
        size_t read(char *buf, size_t size);
        size_t read(ByteBuffer &buf, size_t size);
        size_t append(const char *buf, size_t bufLen);

        void writeCharBuffer(const char *buf, int size = -1);
        void writeString(const std::string &str, int size = -1);
        void writeBool(bool value);
        void writeChar(char value);
        void writeUChar(unsigned char value);
        void writeShort(short value);
        void writeUShort(unsigned short value);
        void writeInt(int value);
        void writeUInt(unsigned int value);
        void writeLong(long value);
        void writeULong(unsigned long value);
        void writeFloat(float value);
        void writeDouble(double value);

        char *readCharBuffer(size_t *b_size, int *err);
        std::string *readString(int *err);
        bool readBool(int *err);
        char readChar(int *err);
        unsigned char readUChar(int *err);
        short readShort(int *err);
        unsigned short readUShort(int *err);
        int readInt(int *err);
        unsigned int readUInt(int *err);
        long readLong(int *err);
        unsigned long readULong(int *err);
        float readFloat(int *err);
        double readDouble(int *err);

        void reserveSize(size_t size);

    protected:
    private:
        size_t offset = 0;
        size_t size = 0;
        size_t capacity = 1024;
        unsigned char *buf = nullptr;
        bool prependSize = false;
};

#endif /* !BYTEBUFFER_HPP_ */
