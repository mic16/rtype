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

void Client::run(std::string ip)
{
    std::cout << "Client Running." << std::endl;
    this->connectTo(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), 3000));
    boost::thread t(boost::bind(&boost::asio::io_context::run, &ioService));
    t.join();
}

void Client::run(std::string ip, int port)
{
    std::cout << "Client Running." << std::endl;
    this->connectTo(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port));
    boost::thread t(boost::bind(&boost::asio::io_context::run, &ioService));
    t.join();
}

void Client::connectTo(const boost::asio::ip::tcp::endpoint &endpoint)
{
    this->endpoint = endpoint;
    this->socket.async_connect(endpoint, [this](const boost::system::error_code& error){
        this->running = this->socket.is_open() ? true : false;
        if (!error) {
            std::cout << "Connection successful." << std::endl;
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
            std::cout << "Read failed." << std::endl;
        }
    });
}

void Client::writeData(std::string data)
{
    int len = data.length();
    std::string size = "";
    while (len != 0) {
        size = (len % 2 == 0 ? "0" : "1") + size;
        len /= 2;
    }
    boost::asio::async_write(this->socket, boost::asio::buffer(size, 8), [this](const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (!error) {
            std::cout << "Data size send : len : " << bytes_transferred << std::endl;
            this->handleData();
        } else {
            std::cout << "write size failed." << std::endl;
            return ;
        }
    });
    boost::asio::async_write(this->socket, boost::asio::buffer(data, data.length()), [this](const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (!error) {
            std::cout << "Data send : len : " << bytes_transferred << std::endl;
            this->handleData();
        } else {
            std::cout << "write data failed." << std::endl;
            return ;
        }
    });
}