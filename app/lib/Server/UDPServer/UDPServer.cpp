/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** UDPServer
*/

#include "lib/Server/UDPServer/UDPServer.hpp"

UDPServer::UDPServer(void): port(0)
{
}

UDPServer::~UDPServer(void)
{
    if (acceptor->is_open()) acceptor->close();
}

bool UDPServer::configure(const std::string &addr, const unsigned int port)
{
    if (!std::regex_match(addr, std::regex("^([0-9]{1,3}(\\.|$)){4}")))
        throw EConnection("Address has invalid pattern. Please test with 127.0.0.1");
    acceptor = std::make_shared<boost::asio::ip::udp::socket>(
        ioService,
        boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(addr), port)
    );

    if (!acceptor->is_open()) { return (false); }
    this->port = acceptor->local_endpoint().port();
    return (true);
}

bool UDPServer::configure(const unsigned int port)
{
    acceptor = std::make_shared<boost::asio::ip::udp::socket>(
        ioService,
        boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)
    );

    if (!acceptor->is_open()) { return (false); }
    this->port = acceptor->local_endpoint().port();
    return (true);
}

void UDPServer::work(void)
{
}

bool UDPServer::run(void)
{
    std::string address = acceptor->local_endpoint().address().to_string();
    port = acceptor->local_endpoint().port();

    if (acceptor->is_open()) {
        std::cout << "Server is running on address:port : " << address << ':' << port << std::endl;
        work();
    }
    m_thread = std::make_unique<boost::thread>(boost::bind(&boost::asio::io_context::run, &ioService));
    return (true);
}

void UDPServer::join()
{
    m_thread->join();
}

void UDPServer::detach()
{
    m_thread->detach();
}

unsigned int UDPServer::getPort() const { return (port); }