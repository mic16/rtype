/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** create
*/

#include "client/Class/GameMenu/GameMenu.hpp"

void GameMenu::tryCreateRoom()
{
    buffer.clear();

    buffer.writeUInt(sizeof(int) + sizeof(unsigned int) + roomname.length() + 1);
    buffer.writeInt(req::Type::CreateRoom);
    buffer.writeCharBuffer(roomname.c_str());

    client->sendData(buffer.flush(), buffer.getSize());
}

void GameMenu::initFixedCreateDrawables()
{
    fixedDrawables.at(sceneName::CREATE).push_back(std::make_unique<sf::Sprite>());
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setTexture(*loadedTextures["background"]);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setOrigin(sf::Vector2f(960, 480));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setPosition(sf::Vector2f(800, 400));

    fixedDrawables.at(sceneName::CREATE).push_back(std::make_unique<sf::Text>());
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setString("Enter the room name:");
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setCharacterSize(40);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setFillColor(sf::Color::White);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setPosition(sf::Vector2f(520, 280));

    fixedDrawables.at(sceneName::CREATE).push_back(std::make_unique<sf::Sprite>());
    sf::Texture backInput;
    backInput.create(600, 80);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setTexture(backInput);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setColor(sf::Color::Black);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setOrigin(sf::Vector2f(300, 40));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setPosition(sf::Vector2f(800, 400));

    fixedDrawables.at(sceneName::CREATE).push_back(std::make_unique<sf::Text>());
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setString("Only alphanumeric roomname is authorized.");
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setCharacterSize(30);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setFillColor(sf::Color::Red);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::CREATE).get())->setPosition(sf::Vector2f(350, 480));
}

void GameMenu::initModCreateDrawables()
{
    modDrawables.at(sceneName::CREATE).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("roomnameInput", std::make_unique<sf::Text>()));
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::CREATE)["roomnameInput"].get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::CREATE)["roomnameInput"].get())->setString("...");
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::CREATE)["roomnameInput"].get())->setCharacterSize(35);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::CREATE)["roomnameInput"].get())->setFillColor(sf::Color::White);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::CREATE)["roomnameInput"].get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::CREATE)["roomnameInput"].get())->setPosition(sf::Vector2f(520, 375));
}