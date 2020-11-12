/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** TCPClient
*/

#include "client/Class/TCPClient/TCPClient.hpp"

TCPClient::TCPClient(IGameMenu *gameMenu): socket(ioService), m_packet(new char[1024]), menu(gameMenu), buffer(1024)
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
    socket.async_connect(this->endpoint,
    [this](const boost::system::error_code& error){
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
    socket.async_read_some(boost::asio::buffer(m_packet, 1024),
    [this](const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (!error) {
            std::cout << "Data received : len : " << bytes_transferred << std::endl;
            buffer.clear();
            buffer.append(m_packet, bytes_transferred);
            bool isMoreData = true;
            int err = 0;
            while (isMoreData) {
                unsigned int expectedDataLen = buffer.readUInt(&err);
                if (!err && expectedDataLen >= bytes_transferred - 4) {
                    std::cout << "Data size is correct sized." << std::endl;
                    this->handleResponses();
                    bytes_transferred -= 4 - expectedDataLen;
                } else {
                    std::cout << "No More data to handle." << std::endl;
                    isMoreData = false;
                    break;
                }
            }
            this->handleData();
        } else {
            std::cout << "Connection failed." << std::endl;
        }
    });
}

void TCPClient::sendData(const unsigned char *buff, const size_t buffLen)
{
    socket.async_write_some(boost::asio::buffer(buff, buffLen),
    [this](const boost::system::error_code &ec, std::size_t bytes_transferred) {
        if (!ec) {
            std::cout << "Data is wrote : " << bytes_transferred << std::endl;
        } else {
            std::cout << "Data isn't sent" << std::endl;
        }
    });
}