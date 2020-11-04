/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameWindow
*/

#ifndef GAMEWINDOW_HPP_
#define GAMEWINDOW_HPP_

#include "lib/SFML.hpp"
#include "lib/Utility.hpp"

// #include "client/Class/Player/Player.hpp"
#include "client/Class/ECS/ECS.hpp"

class GameWindow {
    public:
        GameWindow();
        ~GameWindow();

        void openWindow();
        void draw();
        void checkKeyPressed(sf::Keyboard::Key key);
        void checkKeyReleased(sf::Keyboard::Key key);
        void updatePlayerPosition();
        std::shared_ptr<sf::RectangleShape> initPlayer();

        enum DIRECTION {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

    private:
        std::shared_ptr<sf::RenderWindow> gameWindow;
        // std::shared_ptr<Player> player;
        bool isDirectionMaintained[4];
        sf::Event event;
        std::shared_ptr<sf::RectangleShape> playerShape;
        std::shared_ptr<sf::Texture> playerTexture;
};

#endif /* !GAMEWINDOW_HPP_ */