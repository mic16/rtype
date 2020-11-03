/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Game
*/

#include "client/Class/GameLoop.hpp"

GameLoop::GameLoop() : window(sf::VideoMode(1000, 800), "R-TYPE"),
               client(),
               background(window)
{
    state = GameState::Menu;
}

GameLoop::~GameLoop()
{
}

int GameLoop::loop()
{
    while (window.isOpen()) {
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        background.update();
        background.draw();

        window.display();
    }
    return 0;
}