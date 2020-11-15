/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** UDPClient
*/

#include "server/Class/UDPClient/UDPClient.hpp"

UDPClient::UDPClient(): m_id(UDPClient::genId()), buffer(1024)
{
    m_packet = new char[1024];
}

UDPClient::~UDPClient()
{
    if (m_packet) delete m_packet;
}

bool UDPClient::setClient(const std::shared_ptr<boost::asio::ip::udp::socket> &s_acceptor)
{
    acceptor = s_acceptor;
    m_address = m_endpoint.address().to_string();
    m_port = m_endpoint.port();

    idStr = m_address + ':' + std::to_string(m_port);
    return (true);
}

const std::string &UDPClient::getAddress() const
{ return (m_address); }

const unsigned int UDPClient::getPort() const
{ return (m_port); }

char *UDPClient::getPacket() const
{ return (m_packet); }

void UDPClient::write(const ByteBuffer &buffer)
{
    acceptor->async_send_to(
        boost::asio::buffer(buffer.flush(), buffer.getSize()),
        m_endpoint,
        [this](const boost::system::error_code &errc,  std::size_t bytes_transferred) {
        if (!errc) {
        } else {
            std::cout << "Failed writing to client" << std::endl;
        }
    });
}

ByteBuffer &UDPClient::getBuffer()
{
    return (buffer);
}