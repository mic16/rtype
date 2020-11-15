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
#include "lib/Network/ANetworkClient.hpp"

class UDPClient : public ANetworkClient {
    public:
        UDPClient();
        UDPClient(const UDPClient &copy);
        ~UDPClient();

        void resetId() { m_id = ANetworkClient::genId(); }
        unsigned int getId() const { return m_id; }
        const std::string &getIdStr() const { return idStr; }

        bool setClient(const std::shared_ptr<boost::asio::ip::udp::socket> &s_acceptor);

        const std::string &getAddress() const;
        const unsigned int getPort() const;

        char *getPacket() const;
        void write(const ByteBuffer &buffer);
        ByteBuffer &getBuffer();

        boost::asio::ip::udp::endpoint m_endpoint;

    private:
        unsigned int m_id;
        std::string idStr;
        std::string m_address;
        char *m_packet = nullptr;
        unsigned int m_port;
        std::shared_ptr<boost::asio::ip::udp::socket> acceptor;
        ByteBuffer buffer;
};

#endif /* !UDPCLIENT_HPP_ */
