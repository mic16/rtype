/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** end
*/

#include "client/Class/GameMenu/GameMenu.hpp"

void GameMenu::initFixedEndDrawables()
{
    fixedDrawables.at(sceneName::END).push_back(std::make_unique<sf::Text>());
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setString("GAME\nOVER");
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setCharacterSize(48);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setFillColor(sf::Color::Red);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setPosition(sf::Vector2f(800, 400));
}

void GameMenu::initModEndDrawables()
{

}