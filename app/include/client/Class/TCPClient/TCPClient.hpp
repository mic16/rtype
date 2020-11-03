/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** TCPClient
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_

#include <boost/asio.hpp>
#include <iostream>
#include <vector>

#include "client/Class/Exceptions/EConnection.hpp"

class TCPClient {
    public:
        TCPClient();
        ~TCPClient();

        void run();
        void connectTo(const boost::asio::ip::tcp::endpoint &endpoint);

        void handleData();
        void sendData(const char *buff, const size_t buffLen);
    private:
        boost::asio::io_service ioService;
        boost::asio::ip::tcp::socket socket;
        boost::asio::ip::tcp::endpoint endpoint;
        unsigned char *m_packet = nullptr;
};

#endif /* !TCPCLIENT_HPP_ */

