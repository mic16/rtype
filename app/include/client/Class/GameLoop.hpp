/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "client/Class/Client/Client.hpp"
#include "client/Class/Background/Background.hpp"

enum GameState {
    Error,
    Menu,
    Game
};

class GameLoop {
    public:
        GameLoop();
        ~GameLoop();
        int loop();

    protected:
    private:

        Client client;
        Background background;
        GameState state;
        sf::RenderWindow window;
        sf::Event event;
};

#endif /* !GAME_HPP_ */
