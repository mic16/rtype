/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** room
*/

#include "client/Class/GameMenu/GameMenu.hpp"

void GameMenu::initFixedRoomDrawables()
{
    fixedDrawables.at(sceneName::ROOM).push_back(std::make_unique<sf::Sprite>());
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setTexture(*loadedTextures["background"]);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setOrigin(sf::Vector2f(960, 480));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setPosition(sf::Vector2f(800, 400));

    fixedDrawables.at(sceneName::ROOM).push_back(std::make_unique<sf::Text>());
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setString("Room name ");
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setCharacterSize(45);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setFillColor(sf::Color::White);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setPosition(sf::Vector2f(520, 105));
}

void GameMenu::initModRoomDrawables()
{
    modDrawables.at(sceneName::ROOM).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("roomname", std::make_unique<sf::Text>()));
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["roomname"].get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["roomname"].get())->setString("...");
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["roomname"].get())->setCharacterSize(45);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["roomname"].get())->setFillColor(sf::Color::Yellow);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["roomname"].get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["roomname"].get())->setPosition(sf::Vector2f(850, 105));
}