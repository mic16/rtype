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
        default:
            std::cout << "Unknown / Unhandled response." << std::endl;
    }
}