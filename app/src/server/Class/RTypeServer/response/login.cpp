/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** login
*/

#include "server/Class/RTypeServer/RTypeServer.hpp"

void RTypeServer::responseLogin(const unsigned int client_id)
{
    int err = 0;
    const char *username = clients[client_id]->getBuffer().readCharBuffer(&err);

    clients[client_id]->getBuffer().clear();
    clients[client_id]->getBuffer().writeUInt(sizeof(int) + sizeof(bool));
    clients[client_id]->getBuffer().writeInt(res::Type::LogIn);
    if (err || isUsernameTaken(username)) {
        std::cout << "Error on logIn." << std::endl;
        clients[client_id]->getBuffer().writeBool(false);
        sendData(client_id);
        return;
    }
    std::cout << "LogIn success." << std::endl;
    clients[client_id]->setUsername(username);
    clients[client_id]->getBuffer().writeBool(true);
    sendData(client_id);
}

bool RTypeServer::isUsernameTaken(const std::string &username)
{
    for (std::map<unsigned int, std::unique_ptr<TCPClient>>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->second->getUsername() == username && !username.empty())
            return (true);
    }
    return (false);
}