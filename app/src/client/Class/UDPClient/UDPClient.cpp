/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** UDPClient
*/

#include "client/Class/UDPClient/UDPClient.hpp"

UDPClient::UDPClient(boost::asio::io_context &io_service, const std::string &host, const std::string &port):
    ioService(io_service),
    socket(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)),
    buff(1024)
{
    boost::asio::ip::udp::resolver resolver(ioService);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), host, port);
    boost::asio::ip::udp::resolver::iterator iter = resolver.resolve(query);
    endpoint = *iter;
    packet = new char[1024];
}

UDPClient::~UDPClient()
{
}

void UDPClient::work()
{
    socket.async_receive_from(boost::asio::buffer(packet, 1024), endpoint,
    [this](const boost::system::error_code &errc, std::size_t bytes_transferred) {
        if (!errc) {
            std::cout << "Received: " << bytes_transferred << std::endl;
            work();
        } else {
            std::cout << "Error receive" << std::endl;
        }
    });
}

void UDPClient::run()
{
    work();
    ioService.run();
}

void UDPClient::send() {
    socket.async_send_to(boost::asio::buffer(buff.flush(), buff.getSize()), endpoint,
    [this](const boost::system::error_code &errc, std::size_t bytes_transferred) {
        if (!errc) {
            std::cout << "Sending: " << bytes_transferred << " bytes." << std::endl;
        } else {
            std::cout << "Error sending" << std::endl;
        }
    });
}

ByteBuffer &UDPClient::getBuffer()
{
    return (buff);
}