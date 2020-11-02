/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameServer
*/

#include "server/Class/GameServer/GameServer.hpp"

GameServer::GameServer(): UDPServer()
{
}

GameServer::~GameServer()
{
}

void GameServer::work()
{
    handleConnection();
}

unsigned int GameServer::prepareNewClient()
{
    static unsigned int key = 0;

    key += 1;
    std::pair<std::map<unsigned int, boost::asio::ip::udp::endpoint>::iterator, bool>
        inserted = clients.insert(std::make_pair(key, boost::asio::ip::udp::endpoint()));
    if (!inserted.second) { return (0); }
    return (key);
}

bool GameServer::handleConnection()
{
    unsigned int client_id = prepareNewClient();

    // if (!isClientConnected(client_id)) { return (false); }
    // acceptor->async_accept(clients[client_id],
    // [this, client_id](const boost::system::error_code &errc) {
        // if (!errc) {
            // clients[client_id]->setClient();
            // this->handleClient(client_id);
            // this->handleConnection();
        // } else {
            // std::cout << "Failed connection client" << std::endl;
        // }
    // });
    return (true);
}

bool GameServer::handleClient(const unsigned int client_id)
{
    // if (!isClientConnected(client_id)) { return (false); }
    // std::cout << clients[client_id]->getAddress() << ':' << clients[client_id]->getPort() << std::endl;
    // clients[client_id]->m_socket.async_read_some(boost::asio::buffer(clients[client_id]->getPacket(), 1024),
    // [this, client_id](const boost::system::error_code &errc, std::size_t bytes_transferred) {
    //     if (!errc) {
    //         this->handleClient(client_id);
    //     } else {
    //         disconnectClient(client_id);
    //     }
    // });
    return (true);
}

bool GameServer::disconnectClient(const unsigned int client_id)
{
    if (!isClientConnected(client_id)) { return (false); }
    clients.erase(client_id);
    return (true);
}

bool GameServer::isClientConnected(const unsigned int client_id)
{
    return (clients.count(client_id) > 0);
}

const std::map<unsigned int, boost::asio::ip::udp::endpoint> &GameServer::getClients() const
{
    return (clients);
}