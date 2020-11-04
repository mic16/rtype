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
#include <thread>
#include <map>
#include <cctype>

#include "client/Class/TCPClient/TCPClient.hpp"
#include "client/Class/ResourceLoader/ResourceLoader.hpp"
#include "client/Class/Exceptions/EFinished.hpp"
#include "lib/ByteBuffer/ByteBuffer.hpp"

#define LAST_FIXED_SPRITE(sceneName) fixedDrawables.at(sceneName)[fixedDrawables.at(sceneName).size() - 1]

enum sceneName { LOGIN, MENU, SEARCH, WAITING_ROOM };

class GameMenu : public IGameMenu {
    public:
        GameMenu();
        ~GameMenu();

        int run();

        void draw();
        bool isOpen();

        bool isUsernameValid();

        void handleEvents();
        void handleTextEntered();
        void handleKeyReleased();

        void handleDisplay();
        void tryLogIn();
    private:
        void initDrawables();
        void initFixedLoginDrawables();
        void initModLoginDrawables();

        sceneName scene;
        std::unique_ptr<TCPClient> client;
        std::string username;

        ResourceLoader loadedTextures;
        std::map<sceneName, std::vector<std::unique_ptr<sf::Drawable>>> fixedDrawables;
        std::map<sceneName, std::map<std::string, std::unique_ptr<sf::Drawable>>> modDrawables;
        std::unique_ptr<sf::RenderWindow> window;
        sf::Event event;
        sf::Font mainFont;

        std::unique_ptr<std::thread> displayThread;
        ByteBuffer buffer;
};

#endif /* !GAMEMENU_HPP_ */