/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** login
*/

#include "client/Class/TCPClient/TCPClient.hpp"

void TCPClient::handleStartGame()
{
    int err = 0;
    bool success = buffer.readBool(&err);
    if (err || !success) {
        std::cout << "Game error!" << std::endl;
        return;
    }
    std::cout << "Game success." << std::endl;
    menu->getGameEntities().get()->setGamePlaying(true);
    menu->setScene(sceneName::GAME);
}