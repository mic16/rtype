/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** TCPServer
*/

#include "lib/Server/TCPServer/TCPServer.hpp"

TCPServer::TCPServer(void): port(0)
{
}

TCPServer::~TCPServer(void)
{
    if (acceptor->is_open()) acceptor->close();
}

bool TCPServer::configure(const unsigned int port)
{
    acceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(
        ioService,
        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)
    );

    if (!acceptor->is_open()) { return (false); }
    this->port = port;
    return (true);
}

void TCPServer::work(void)
{
}

bool TCPServer::run(void)
{
    acceptor->listen();
    std::string address = acceptor->local_endpoint().address().to_string();
    port = acceptor->local_endpoint().port();

    if (acceptor->is_open()) {
        std::cout << "Server is running on address:port : " << address << ':' << port << std::endl;
        work();
    }
    boost::thread t(boost::bind(&boost::asio::io_context::run, &ioService));
    t.join();
    return (true);
}

unsigned int TCPServer::getPort() const { return (port); }