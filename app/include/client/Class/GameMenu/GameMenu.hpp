/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameMenu
*/

#ifndef GAMEMENU_HPP_
#define GAMEMENU_HPP_

#include "SFML/Graphics.hpp"
#include <memory>

#include "client/Class/TCPClient/TCPClient.hpp"

enum sceneName { MENU, SEARCH, WAITING_ROOM };

class GameMenu {
    public:
        GameMenu();
        ~GameMenu();

        int run();
        void handleEvents();
    private:
        sceneName scene;
        std::unique_ptr<TCPClient> client;

        std::unique_ptr<sf::RenderWindow> window;
        sf::Event event;
};

#endif /* !GAMEMENU_HPP_ */