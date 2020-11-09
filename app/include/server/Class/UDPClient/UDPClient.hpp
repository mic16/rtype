/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** UDPClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include <boost/asio.hpp>
#include <string>

class UDPClient {
    public:
        UDPClient();
        ~UDPClient();

        bool setClient(void);

        const std::string &getAddress() const;
        const unsigned int getPort() const;

        boost::asio::ip::udp::endpoint m_endpoint;
        unsigned char *getPacket() const;

    private:
        std::string m_address;
        unsigned char *m_packet = nullptr;
        unsigned int m_port;
};

#endif /* !UDPCLIENT_HPP_ */
