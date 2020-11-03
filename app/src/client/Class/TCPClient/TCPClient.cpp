/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** TCPClient
*/

#include "client/Class/TCPClient/TCPClient.hpp"

TCPClient::TCPClient(): socket(ioService)
{
}

TCPClient::~TCPClient()
{
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
    // boost::asio::async_read(this->socket, boost::asio::buffer(msg, 17), [this, msg](const boost::system::error_code& error, std::size_t bytes_transferred)
    // {
        // if (!error) {
            // std::cout << "Data received : len : " << bytes_transferred << std::endl;
            // for (int i = 0; i < 17; i++)
                // std::cout << msg[i] << std::endl;
            // this->handleData();
        // } else {
            // std::cout << "Connection failed." << std::endl;
        // }
    // });
}