/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameMenu
*/

#include "client/Class/GameMenu/GameMenu.hpp"

GameMenu::GameMenu(): window(std::make_unique<sf::RenderWindow>(sf::VideoMode(1600, 800), "SFML window", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize))
{
}

GameMenu::~GameMenu()
{
}

int GameMenu::run()
{
    while (this->window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
    }
    return (0);
}