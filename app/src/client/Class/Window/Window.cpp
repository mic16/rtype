/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Window
*/

#include "client/Class/Window/Window.hpp"

Window::Window() : gameEntities()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "SFML window", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    player = std::make_shared<Player>();
    for (int i = 0; i != 4 ; i++)
        isDirectionMaintained[i] = false;
    openWindow();
    gameEntities.setWindow(this->window);
    gameEntities.init();
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
        updatePlayerPosition();
        player->getPlayerAnimation()->update(0, deltaTime, isDirectionMaintained[DIRECTION::UP], isDirectionMaintained[DIRECTION::DOWN]);
        player->getPlayerShape()->setTextureRect(player->getPlayerAnimation()->getUvRect());
        draw();
    }
}

void Window::updatePlayerPosition()
{
    if (isDirectionMaintained[DIRECTION::UP])
        player.get()->setPosition(0, -0.1);
    if (isDirectionMaintained[DIRECTION::DOWN])
        player.get()->setPosition(0, 0.1);
    if (isDirectionMaintained[DIRECTION::LEFT])
        player.get()->setPosition(-0.1, 0);
    if (isDirectionMaintained[DIRECTION::RIGHT])
        player.get()->setPosition(0.1, 0);
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

void Window::draw()
{

    window.get()->clear(sf::Color(150, 150, 150));
    // window.get()->draw(player->getPlayerShape()[0]);

    gameEntities.update();
    window.get()->display();
}