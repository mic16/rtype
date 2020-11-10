/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** UDPClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include "lib/ByteBuffer/ByteBuffer.hpp"

class UDPClient {
    public:
        UDPClient(boost::asio::io_context &io_service, const std::string &host, const std::string &port);
        ~UDPClient();

        void work();
        void run();
        void send();

        ByteBuffer &getBuffer();

    private:
        boost::asio::io_context &ioService;
        boost::asio::ip::udp::socket socket;
        boost::asio::ip::udp::endpoint endpoint;
        char *packet = nullptr;
        ByteBuffer buff;
};

#endif /* !UDPCLIENT_HPP_ */
