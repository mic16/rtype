/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** UDPClient
*/

#include "client/Class/UDPClient/UDPClient.hpp"

UDPClient::UDPClient(boost::asio::io_context &io_service, const std::string &host, const std::string &port):
    networkHandler(1024),
    client(new RemoteClient(io_service, host, port))
{
}

UDPClient::~UDPClient()
{
}

void UDPClient::work()
{
    client->socket.async_receive_from(boost::asio::buffer(client->packet, 1024), client->endpoint,
    [this](const boost::system::error_code &errc, std::size_t bytes_transferred) {
        if (!errc) {
            client->getBuffer().append(client->packet, bytes_transferred);
            networkHandler.processMessage(*client);
            work();
        } else {
            std::cout << "Error receive" << std::endl;
        }
    });
}

void UDPClient::run()
{
    work();
    client->ioService.run();
}

void UDPClient::connect()
{
    client->getBuffer().writeInt(666);
    client->write(client->getBuffer());
    client->getBuffer().clear();
    networkHandler.addClient(client);
}