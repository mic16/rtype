/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** Client
*/

#include "client/Class/Client/Client.hpp"
#include <unistd.h>

Client::Client(): running(false), socket(this->ioService)
{
}

Client::~Client()
{
}

bool Client::isRunning() const
{
    return (running);
}

void Client::run()
{
    std::cout << "Client Running." << std::endl;
    this->connectTo(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("10.101.52.74"), 3000));
    this->ioService.run();
}

void Client::connectTo(const boost::asio::ip::tcp::endpoint &endpoint)
{
    this->endpoint = endpoint;
    this->socket.async_connect(endpoint, [this](const boost::system::error_code& error){
        this->running = this->socket.is_open() ? true : false;
        if (!error) {
            std::cout << "Connection succedded." << std::endl;
            this->handleData();
        } else {
            std::cout << "Connection failed." << std::endl;
        }
    });
}

void Client::handleData()
{
    boost::asio::async_read(this->socket, boost::asio::buffer(this->msg, 17), [this](const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (!error) {
            std::cout << "Data received : len : " << bytes_transferred << std::endl;
            for (int i = 0; i < 17; i++)
                std::cout << this->msg[i] << std::endl;
            this->handleData();
        } else {
            std::cout << "Connection failed." << std::endl;
        }
    });
}