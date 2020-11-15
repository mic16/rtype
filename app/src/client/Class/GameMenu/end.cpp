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
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setCharacterSize(80);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setFillColor(sf::Color::Red);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setPosition(sf::Vector2f(675, 150));

    fixedDrawables.at(sceneName::END).push_back(std::make_unique<sf::Text>());
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setString("You survived");
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setCharacterSize(20);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setFillColor(sf::Color::Black);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setPosition(sf::Vector2f(700, 450));

    fixedDrawables.at(sceneName::END).push_back(std::make_unique<sf::Text>());
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setString("seconds");
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setCharacterSize(20);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setFillColor(sf::Color::Black);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::END).get())->setPosition(sf::Vector2f(735, 500));
}

void GameMenu::initModEndDrawables()
{
    modDrawables.at(sceneName::END).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("score", std::make_unique<sf::Text>()));
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::END)["score"].get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::END)["score"].get())->setString("");
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::END)["score"].get())->setCharacterSize(20);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::END)["score"].get())->setFillColor(sf::Color::Black);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::END)["score"].get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::END)["score"].get())->setPosition(sf::Vector2f(735, 475));
}