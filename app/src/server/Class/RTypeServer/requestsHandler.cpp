/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** requestsHandler
*/

#include "server/Class/RTypeServer/RTypeServer.hpp"

void RTypeServer::handleRequests(const unsigned int client_id)
{
    switch (static_cast<req::Type>(clients[client_id]->getBuffer().readInt(nullptr))) {
        case req::Type::LogIn:
            std::cout << "LogIn request." << std::endl;
            responseLogin(client_id);
            break;
        case req::Type::CreateRoom:
            std::cout << "CreateRoom request." << std::endl;
            responseCreateRoom(client_id);
            break;
        case req::Type::JoinRoom:
            std::cout << "JoinRoom request." << std::endl;
            // responseJoinRoom(client_id);
            break;
        default:
            std::cout << "Unknown request type." << std::endl;
    }
}