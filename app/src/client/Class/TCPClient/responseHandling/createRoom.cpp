/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** createRoom
*/

#include "client/Class/TCPClient/TCPClient.hpp"

void TCPClient::handleCreateRoom()
{
    int err = 0;
    bool success = buffer.readBool(&err);
    if (err || !success) {
        std::cout << "CreateRoom error!" << std::endl;
        return;
    }
    std::cout << "CreateRoom success." << std::endl;
    menu->setScene(sceneName::ROOM);
}