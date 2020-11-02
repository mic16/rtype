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

class TCPClient {
    public:
        TCPClient(boost::asio::io_service &service);
        ~TCPClient();

        bool setClient(void);

        const std::string &getAddress() const;
        const unsigned int getPort() const;

        boost::asio::ip::tcp::socket m_socket;
        unsigned char *getPacket() const;

    private:
        std::string m_address;
        unsigned char *m_packet = nullptr;
        unsigned int m_port;
        char *m_username = nullptr;
};

#endif /* !TCPCLIENT_HPP_ */
