/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** initSprites
*/

#include "client/Class/GameMenu/GameMenu.hpp"

void GameMenu::initFixedSprites()
{
    fixedSprites.insert(std::pair<sceneName, std::vector<std::unique_ptr<sf::Sprite>>>(sceneName::MENU, std::vector<std::unique_ptr<sf::Sprite>>()));

    initFixedMenuSprites();
}

void GameMenu::initFixedMenuSprites()
{
    fixedSprites.at(sceneName::MENU).push_back(std::make_unique<sf::Sprite>());
    LAST_FIXED_SPRITE(sceneName::MENU)->setTexture(*loadedTextures["background"]);
    LAST_FIXED_SPRITE(sceneName::MENU)->setOrigin(sf::Vector2f(960, 480));
    LAST_FIXED_SPRITE(sceneName::MENU)->setPosition(sf::Vector2f(800, 400));
}