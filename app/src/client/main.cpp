/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** main
*/

#include "SFML/Graphics.hpp"
#include "client/Class/GameMenu/GameMenu.hpp"

int main()
{
    // ResourceLoader rl("./app/assets/");
    GameMenu menu;

    return menu.run();
}