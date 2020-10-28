/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** AServer
*/

#include "server/Class/AServer/AServer.hpp"

AServer::AServer(void): port(0)
{
}

AServer::~AServer(void)
{
    if (acceptor->is_open()) acceptor->close();
}

bool AServer::configure(const unsigned int port)
{
    acceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(
        ioService,
        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)
    );

    if (!acceptor->is_open()) { return (false); }
    this->port = port;
    return (true);
}

void AServer::work(void)
{
}

bool AServer::run(void)
{
    acceptor->listen();
    std::string address = acceptor->local_endpoint().address().to_string();
    port = acceptor->local_endpoint().port();

    if (acceptor->is_open()) {
        std::cout << "Server is running on address:port : " << address << ':' << port << std::endl;
        work();
    }
    this->ioService.run();
}

unsigned int AServer::getPort() const { return (port); }