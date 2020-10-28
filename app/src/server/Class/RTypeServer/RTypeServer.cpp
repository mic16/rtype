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

void RTypeServer::handleConnection()
{
    clients.emplace_back(std::make_unique<Client>(ioService));

    acceptor->async_accept(clients[clients.size() - 1]->m_socket,
    [this](const boost::system::error_code &errc) {
        if (!errc) {
            clients[clients.size() - 1]->setClient();
            this->handleClient(clients[clients.size() - 1]);
            this->handleConnection();
        } else {
            std::cout << "Failed connection client" << std::endl;
        }
    });
}

void RTypeServer::handleClient(const Client &client)
{
}