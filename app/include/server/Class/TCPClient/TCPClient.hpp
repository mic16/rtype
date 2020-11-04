/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** TCPClient
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_

#include <boost/asio.hpp>
#include <string>

#include "lib/ByteBuffer/ByteBuffer.hpp"
#include "lib/request.h"
#include "lib/response.h"

class TCPClient {
    public:
        TCPClient(boost::asio::io_service &service);
        ~TCPClient();

        bool setClient(void);

        void setUsername(const std::string &username);
        const std::string &getUsername() const;

        ByteBuffer &getBuffer();

        const std::string &getAddress() const;
        const unsigned int getPort() const;

        boost::asio::ip::tcp::socket m_socket;
        char *getPacket() const;

    private:
        std::string m_address;
        char *m_packet = nullptr;
        unsigned int m_port;
        std::string m_username;
        ByteBuffer buffer;
};

#endif /* !TCPCLIENT_HPP_ */
