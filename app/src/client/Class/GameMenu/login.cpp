/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** login
*/

#include "client/Class/GameMenu/GameMenu.hpp"

void GameMenu::tryLogIn()
{
    buffer.clear();

    buffer.writeUInt(sizeof(int) + sizeof(unsigned int) + username.length() + 1);
    buffer.writeInt(req::Type::LogIn);
    buffer.writeCharBuffer(username.c_str());

    client->sendData(buffer.flush(), buffer.getSize());
}

void GameMenu::initFixedLoginDrawables()
{
    fixedDrawables.at(sceneName::LOGIN).push_back(std::make_unique<sf::Sprite>());
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setTexture(*loadedTextures["background"]);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setOrigin(sf::Vector2f(960, 480));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setPosition(sf::Vector2f(800, 400));

    fixedDrawables.at(sceneName::LOGIN).push_back(std::make_unique<sf::Text>());
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setString("Enter your Username:");
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setCharacterSize(40);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setFillColor(sf::Color::White);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setPosition(sf::Vector2f(520, 280));

    fixedDrawables.at(sceneName::LOGIN).push_back(std::make_unique<sf::Sprite>());
    sf::Texture backInput;
    backInput.create(600, 80);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setTexture(backInput);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setColor(sf::Color::Black);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setOrigin(sf::Vector2f(300, 40));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setPosition(sf::Vector2f(800, 400));

    fixedDrawables.at(sceneName::LOGIN).push_back(std::make_unique<sf::Text>());
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setString("Only alphanumeric username is authorized.");
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setCharacterSize(30);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setFillColor(sf::Color::Red);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setPosition(sf::Vector2f(350, 480));
}

void GameMenu::initModLoginDrawables()
{
    modDrawables.at(sceneName::LOGIN).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("usernameInput", std::make_unique<sf::Text>()));
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::LOGIN)["usernameInput"].get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::LOGIN)["usernameInput"].get())->setString(username);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::LOGIN)["usernameInput"].get())->setCharacterSize(35);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::LOGIN)["usernameInput"].get())->setFillColor(sf::Color::White);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::LOGIN)["usernameInput"].get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::LOGIN)["usernameInput"].get())->setPosition(sf::Vector2f(520, 375));
}