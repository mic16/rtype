/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "lib/SFML.hpp"
#include "lib/Utility.hpp"

#include "client/Class/Player/Player.hpp"
#include "client/Class/GameEntities/GameEntities.hpp"

class Window {
    public:
        Window();
        ~Window();

        void openWindow();
        void draw();
        void checkKeyPressed(sf::Keyboard::Key key);
        void checkKeyReleased(sf::Keyboard::Key key);
        void updatePlayerPosition();

        enum DIRECTION {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

    private:
        std::shared_ptr<sf::RenderWindow> window;
        std::shared_ptr<Player> player;
        bool isDirectionMaintained[4];
        GameEntities gameEntities;
};

#endif /* !WINDOW_HPP_ */