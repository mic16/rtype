/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** main
*/

#include "SFML/Graphics.hpp"
#include <utility>

class Window
{
public:
    Window();
    ~Window();

    void openWindow();
private:
    std::unique_ptr<sf::RenderWindow> window;

};