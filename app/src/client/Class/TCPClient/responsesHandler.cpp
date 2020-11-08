/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** responsesHandler
*/

#include "client/Class/TCPClient/TCPClient.hpp"

void TCPClient::handleResponses()
{
    switch (static_cast<res::Type>(buffer.readInt(nullptr))) {
        case res::Type::LogIn:
            std::cout << "Handle LogIn response." << std::endl;
            handleLogIn();
            break;
        case res::Type::CreateRoom:
            std::cout << "Handle CreateRoom response." << std::endl;
            handleCreateRoom();
            break;
        case res::Type::JoinRoom:
            std::cout << "Handle JoinRoom response." << std::endl;
            handleJoinRoom();
            break;
        case res::Type::listPlayersInRoom:
            std::cout << "Handler listing players response." << std::endl;
            handleListPlayersInRoom();
            break;
        default:
            std::cout << "Unknown / Unhandled response." << std::endl;
    }
}