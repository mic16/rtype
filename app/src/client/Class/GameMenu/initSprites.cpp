/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** initSprites
*/

#include "client/Class/GameMenu/GameMenu.hpp"

void GameMenu::initDrawables()
{
    fixedDrawables.insert(std::pair<sceneName, std::vector<std::unique_ptr<sf::Drawable>>>(sceneName::LOGIN, std::vector<std::unique_ptr<sf::Drawable>>()));
    modDrawables.insert(std::pair<sceneName, std::map<std::string, std::unique_ptr<sf::Drawable>>>(sceneName::LOGIN, std::map<std::string, std::unique_ptr<sf::Drawable>>()));

    initFixedLoginDrawables();
    initModLoginDrawables();
}