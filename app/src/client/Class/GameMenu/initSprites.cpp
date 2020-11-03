/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** initSprites
*/

#include "client/Class/GameMenu/GameMenu.hpp"

void GameMenu::initFixedSprites()
{
    fixedSprites.insert(std::pair<sceneName, std::vector<sf::Sprite>>(sceneName::MENU, std::vector<sf::Sprite>()));

    initFixedMenuSprites();
}

void GameMenu::initFixedMenuSprites()
{
    fixedSprites.at(sceneName::MENU).push_back(sf::Sprite());
    LAST_FIXED_SPRITE(sceneName::MENU).setTexture(loadedTextures["background"]);
}