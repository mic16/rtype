/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** RemoteClient
*/

#ifndef REMOTECLIENT_HPP_
#define REMOTECLIENT_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include "lib/Network/INetworkClient.hpp"
#include "lib/ByteBuffer/ByteBuffer.hpp"

class RemoteClient : public INetworkClient {
    public:
        RemoteClient(boost::asio::io_context &io_service, const std::string &host, const std::string &port);
        ~RemoteClient();

        void write(const ByteBuffer &buffer);
        ByteBuffer &getBuffer();

        char *packet = nullptr;
        boost::asio::io_context &ioService;
        boost::asio::ip::udp::socket socket;
        boost::asio::ip::udp::endpoint endpoint;

    private:
        ByteBuffer buff;
};

#endif /* !REMOTECLIENT_HPP_ */