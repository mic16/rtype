/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** RemoteClient
*/

#include "client/Class/UDPClient/RemoteClient.hpp"

RemoteClient::RemoteClient(boost::asio::io_context &io_service, const std::string &host, const std::string &port):
    m_id(RemoteClient::genId()),
    ioService(io_service),
    socket(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 3334)),
    buff(1024)
{
    boost::asio::ip::udp::resolver resolver(ioService);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), host, port);
    boost::asio::ip::udp::resolver::iterator iter = resolver.resolve(query);
    endpoint = *iter;
    packet = new char[1024];
}

RemoteClient::~RemoteClient()
{
}

void RemoteClient::write(const ByteBuffer &buffer)
{
    socket.async_send_to(boost::asio::buffer(buffer.flush(), buffer.getSize()), endpoint,
    [this](const boost::system::error_code &errc, std::size_t bytes_transferred) {
        if (!errc) {
            // std::cout << "Sending: " << bytes_transferred << " bytes." << std::endl;
        } else {
            std::cout << "Error sending" << std::endl;
        }
    });
}

ByteBuffer &RemoteClient::getBuffer()
{
    return (buff);
}