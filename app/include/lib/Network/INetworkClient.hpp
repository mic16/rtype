/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** INetworkClient
*/

#ifndef INETWORKCLIENT_HPP_
#define INETWORKCLIENT_HPP_

#include "lib/ByteBuffer/ByteBuffer.hpp"

class INetworkClient {
    public:
        virtual void write(const ByteBuffer &buffer) = 0;
        virtual ByteBuffer &getBuffer() = 0;

        virtual unsigned int getId() const = 0;
};

#endif /* !INETWORKCLIENT_HPP_ */
