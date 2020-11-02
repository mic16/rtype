/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameServer
*/

#include "server/Class/GameServer/GameServer.hpp"

GameServer::GameServer(): UDPServer(), client(std::make_unique<UDPClient>())
{
}

GameServer::~GameServer()
{
}

void GameServer::work()
{
    handleConnection();
}

bool GameServer::handleConnection()
{
    acceptor->async_receive_from(boost::asio::buffer(client->getPacket(), 1024),
    client->m_endpoint,
    [this](const boost::system::error_code &errc,  std::size_t bytes_transferred) {
        if (!errc) {
            client->setClient();
            std::cout << "Client " << client->getAddress() << ':'
                << client->getPort() << std::endl;
            this->handleConnection();
        } else {
            std::cout << "Failed connection client" << std::endl;
        }
    });
    return (true);
}

const std::unique_ptr<UDPClient> &GameServer::getClients() const
{
    return (client);
}