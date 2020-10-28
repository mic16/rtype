/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** RTypeServer
*/

#include "server/Class/RTypeServer/RTypeServer.hpp"

RTypeServer::RTypeServer() : AServer()
{
}

RTypeServer::~RTypeServer()
{
}

void RTypeServer::work()
{
    handleConnection();
}

unsigned int RTypeServer::prepareNewClient()
{
    static unsigned int key = 0;

    key += 1;
    std::pair<std::map<unsigned int, std::unique_ptr<Client>>::iterator, bool>
        inserted = clients.insert(std::make_pair(key, std::make_unique<Client>(ioService)));
    if (!inserted.second) { return (0); }
    return (key);
}

bool RTypeServer::handleConnection()
{
    unsigned int client_id = prepareNewClient();

    if (clients.count(client_id) <= 0) { return (false); }
    acceptor->async_accept(clients[client_id]->m_socket,
    [this, client_id](const boost::system::error_code &errc) {
        if (!errc) {
            clients[client_id]->setClient();
            this->handleClient(client_id);
            this->handleConnection();
        } else {
            std::cout << "Failed connection client" << std::endl;
        }
    });
    return (true);
}

bool RTypeServer::handleClient(const unsigned int client_id)
{
    if (clients.count(client_id) <= 0) { return (false); }
    /*client->m_socket.async_read_some(boost::asio::buffer(client->m_packet, 1024),
    [this, &client](const boost::system::error_code &errc, std::size_t bytes_transferred) {
        if (!errc) {
            this->handleClient(client);
        } else {
        }
    });*/
    return (true);
}