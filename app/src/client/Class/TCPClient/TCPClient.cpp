/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** TCPClient
*/

#include "client/Class/TCPClient/TCPClient.hpp"

TCPClient::TCPClient(): socket(ioService), m_packet(new unsigned char[1024])
{
}

TCPClient::~TCPClient()
{
    if (m_packet) delete m_packet;
}

void TCPClient::run()
{
    std::cout << "Client Running." << std::endl;
    ioService.run();
}

void TCPClient::connectTo(const boost::asio::ip::tcp::endpoint &endpoint)
{
    this->endpoint = endpoint;
    socket.async_connect(this->endpoint, [this](const boost::system::error_code& error){
        if (!error) {
            std::cout << "Connection succedded." << std::endl;
            this->handleData();
        } else {
            throw EConnection("Connection refused. You should not pass !");
        }
    });
}

void TCPClient::handleData()
{
    boost::asio::async_read(socket, boost::asio::buffer(m_packet, 1024), [this](const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (!error) {
            std::cout << "Data received : len : " << bytes_transferred << std::endl;
            this->handleData();
        } else {
            std::cout << "Connection failed." << std::endl;
        }
    });
}

void TCPClient::sendData(const unsigned char *buff, const size_t buffLen)
{
    boost::asio::async_write(socket, boost::asio::buffer(buff, buffLen),
    [this](const boost::system::error_code &ec, std::size_t bytes_transferred) {
        if (!ec) {
            std::cout << "Data is wrote : " << bytes_transferred << std::endl;
        } else {
            std::cout << "Data isn't sent" << std::endl;
        }
    });
}