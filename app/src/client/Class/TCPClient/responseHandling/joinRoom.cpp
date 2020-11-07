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
    menu->setScene(sceneName::MENU);
}