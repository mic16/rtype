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
#include <memory>
#include "lib/ByteBuffer/ByteBuffer.hpp"
#include "lib/Network/INetworkClient.hpp"

class UDPClient : public INetworkClient {
    public:
        UDPClient();
        ~UDPClient();

        bool setClient(const std::shared_ptr<boost::asio::ip::udp::socket> &s_acceptor);

        const std::string &getAddress() const;
        const unsigned int getPort() const;

        boost::asio::ip::udp::endpoint m_endpoint;
        unsigned char *getPacket() const;
        void write(const ByteBuffer &buffer);

    private:
        std::string m_address;
        unsigned char *m_packet = nullptr;
        unsigned int m_port;
        std::shared_ptr<boost::asio::ip::udp::socket> acceptor;
};

#endif /* !UDPCLIENT_HPP_ */
