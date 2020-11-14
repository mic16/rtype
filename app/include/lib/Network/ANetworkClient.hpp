/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** ANetworkClient
*/

#ifndef ANETWORKCLIENT_HPP_
#define ANETWORKCLIENT_HPP_

#include "lib/ByteBuffer/ByteBuffer.hpp"
#include "lib/Network/INetworkClient.hpp"

class ANetworkClient : public INetworkClient {
    public:
        virtual void write(const ByteBuffer &buffer) = 0;
        virtual ByteBuffer &getBuffer() = 0;

        virtual unsigned int getId() const = 0;

        static unsigned int genId() {
            static unsigned int id = 0;
            id += 1;
            return id;
        }

    private:
};

#endif /* !ANETWORKCLIENT_HPP_ */