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
#include <map>

#include "client/Class/TCPClient/TCPClient.hpp"
#include "client/Class/ResourceLoader/ResourceLoader.hpp"

#define LAST_FIXED_SPRITE(sceneName) fixedSprites.at(sceneName)[fixedSprites.at(sceneName).size() - 1]

enum sceneName { MENU, SEARCH, WAITING_ROOM };

class GameMenu {
    public:
        GameMenu();
        ~GameMenu();

        int run();

        void draw();
        void handleEvents();
    private:
        void initFixedSprites();
        void initFixedMenuSprites();

        sceneName scene;
        std::unique_ptr<TCPClient> client;

        ResourceLoader loadedTextures;
        std::map<sceneName, std::vector<sf::Sprite>> fixedSprites;
        std::unique_ptr<sf::RenderWindow> window;
        sf::Event event;
};

#endif /* !GAMEMENU_HPP_ */