/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** menu
*/

#include "client/Class/GameMenu/GameMenu.hpp"

void GameMenu::initFixedMenuDrawables()
{
    fixedDrawables.at(sceneName::MENU).push_back(std::make_unique<sf::Sprite>());
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::MENU).get())->setTexture(*loadedTextures["background"]);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::MENU).get())->setOrigin(sf::Vector2f(960, 480));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::MENU).get())->setPosition(sf::Vector2f(800, 400));
}

void GameMenu::initModMenuDrawables()
{
    modDrawables.at(sceneName::MENU).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("username", std::make_unique<sf::Text>()));
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["username"].get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["username"].get())->setString(username);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["username"].get())->setCharacterSize(35);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["username"].get())->setFillColor(sf::Color::Yellow);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["username"].get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["username"].get())->setPosition(sf::Vector2f(20, 15));

    modDrawables.at(sceneName::MENU).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("createRoom", std::make_unique<sf::Text>()));
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["createRoom"].get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["createRoom"].get())->setString("Create a room");
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["createRoom"].get())->setCharacterSize(70);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["createRoom"].get())->setFillColor(sf::Color::Yellow);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["createRoom"].get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["createRoom"].get())->setPosition(sf::Vector2f(500, 255));

    modDrawables.at(sceneName::MENU).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("joinRoom", std::make_unique<sf::Text>()));
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["joinRoom"].get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["joinRoom"].get())->setString("Join a room");
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["joinRoom"].get())->setCharacterSize(70);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["joinRoom"].get())->setFillColor(sf::Color::White);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["joinRoom"].get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)["joinRoom"].get())->setPosition(sf::Vector2f(550, 455));
}