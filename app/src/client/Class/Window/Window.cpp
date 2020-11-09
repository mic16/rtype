/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Window
*/

#include "client/Class/Window/Window.hpp"

Window::Window() : gameEntities(window)
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "SFML window", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    for (int i = 0; i != 4 ; i++)
        isDirectionMaintained[i] = false;
    openWindow();
}

Window::~Window()
{
}

void Window::openWindow()
{
    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window->isOpen()) {
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::KeyPressed)
                checkKeyPressed(event.key.code);
            if (event.type == sf::Event::KeyReleased)
                checkKeyReleased(event.key.code);
                    
        }
        window->clear();
        gameEntities.update(isDirectionMaintained, deltaTime, window);
        window->display();
    }
}

void Window::checkKeyReleased(sf::Keyboard::Key key)
{
    switch (key) {
        case (sf::Keyboard::Z):
            isDirectionMaintained[DIRECTION::UP] = false;
            break;
        case (sf::Keyboard::Q):
            isDirectionMaintained[DIRECTION::LEFT] = false;
            break;
        case (sf::Keyboard::S):
            isDirectionMaintained[DIRECTION::DOWN] = false;
            break;
        case (sf::Keyboard::D):
            isDirectionMaintained[DIRECTION::RIGHT] = false;
            break;
        default:
            break;
    }
}

void Window::checkKeyPressed(sf::Keyboard::Key key)
{
    switch (key) {
        case (sf::Keyboard::Z):
            isDirectionMaintained[DIRECTION::UP] = true;
            break;
        case (sf::Keyboard::Q):
            isDirectionMaintained[DIRECTION::LEFT] = true;
            break;
        case (sf::Keyboard::S):
            isDirectionMaintained[DIRECTION::DOWN] = true;
            break;
        case (sf::Keyboard::D):
            isDirectionMaintained[DIRECTION::RIGHT] = true;
            break;
        default:
            break;
    }
}