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
            handleLogIn();
            break;
        case res::Type::CreateRoom:
            handleCreateRoom();
            break;
        case res::Type::JoinRoom:
            handleJoinRoom();
            break;
        case res::Type::listPlayersInRoom:
            handleListPlayersInRoom();
            break;
        case res::Type::SendInfoServer:
            handleInfoServer();
            break;
        default:
            std::cout << "Unknown / Unhandled response." << std::endl;
    }
}