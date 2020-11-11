/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** joinRoom
*/

#include "client/Class/TCPClient/TCPClient.hpp"

void TCPClient::handleJoinRoom()
{
    int err = 0;
    bool success = buffer.readBool(&err);
    if (err || !success) {
        std::cout << "JoinRoom error!" << std::endl;
        return;
    }
    std::cout << "JoinRoom success." << std::endl;
    menu->setScene(sceneName::ROOM);
}

void TCPClient::handleStartGame()
{
    menu->setScene(sceneName::GAME);
}

void TCPClient::handleInfoServer()
{
    int err = 0;
    char *address = buffer.readCharBuffer(nullptr, &err);
    unsigned int port = buffer.readUInt(&err);

    if (err) {
        std::cout << "Cannot get Info Server" << std::endl;
    }
    std::cout << "Server info: " << address << ':' << port << std::endl;
}