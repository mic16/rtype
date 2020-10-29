/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** main
*/

#include "Window.hpp"

Window::Window()
{
    this->window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(800, 600), "SFML window", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize));
    openWindow();
}

Window::~Window()
{
}

void Window::openWindow()
{
    while (this->window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
    }
}