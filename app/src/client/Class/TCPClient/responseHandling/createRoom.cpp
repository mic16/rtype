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

void TCPClient::handleListPlayersInRoom()
{
    int err = 0;
    unsigned int nbPlayers = buffer.readUInt(&err);
    for (size_t i = 0; i < nbPlayers; i++) {
        char *username = nullptr;
        bool isReady = false;
        std::string userid = std::to_string(i + 1);
        if (i < nbPlayers) {
            username = buffer.readCharBuffer(nullptr, &err);
            isReady = buffer.readBool(&err);
            std::cout << username << " is in the lobby." << std::endl;
            menu->setDrawableTextStr(menu->getScene(), "users" + userid, username);
            isReady \
                ? menu->setDrawableSpriteTexture(menu->getScene(), "status" + userid, "ready")
                : menu->setDrawableSpriteTexture(menu->getScene(), "status" + userid, "notready");
            if (menu->getUsername() == std::string(username))
                menu->setDrawableTextColor(menu->getScene(), "users" + userid, sf::Color::Yellow);
        } else {
            menu->setDrawableTextStr(menu->getScene(), "users" + userid, "Waiting players");
            menu->setDrawableSpriteTexture(menu->getScene(), "status" + userid, "waiting");
        }
    }
    if (err) {
        std::cout << "List players in room error!" << std::endl;
        return;
    }
    std::cout << "ListPlayerInRoom success." << std::endl;
}