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

    sf::Texture texture;
    texture.create(600, 400);
    fixedDrawables.at(sceneName::ROOM).push_back(std::make_unique<sf::Sprite>());
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setTexture(texture);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setOrigin(sf::Vector2f(300, 200));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setPosition(sf::Vector2f(800, 400));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setColor(sf::Color::White);

    texture.create(600, 98);
    fixedDrawables.at(sceneName::ROOM).push_back(std::make_unique<sf::Sprite>());
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setTexture(texture);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setOrigin(sf::Vector2f(300, 49));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setPosition(sf::Vector2f(800, 250));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setColor(sf::Color::Black);

    texture.create(600, 98);
    fixedDrawables.at(sceneName::ROOM).push_back(std::make_unique<sf::Sprite>());
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setTexture(texture);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setOrigin(sf::Vector2f(300, 49));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setPosition(sf::Vector2f(800, 350));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setColor(sf::Color::Black);

    texture.create(600, 98);
    fixedDrawables.at(sceneName::ROOM).push_back(std::make_unique<sf::Sprite>());
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setTexture(texture);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setOrigin(sf::Vector2f(300, 49));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setPosition(sf::Vector2f(800, 450));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setColor(sf::Color::Black);

    texture.create(600, 98);
    fixedDrawables.at(sceneName::ROOM).push_back(std::make_unique<sf::Sprite>());
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setTexture(texture);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setOrigin(sf::Vector2f(300, 49));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setPosition(sf::Vector2f(800, 550));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::ROOM).get())->setColor(sf::Color::Black);
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

    modDrawables.at(sceneName::ROOM).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("users1", std::make_unique<sf::Text>()));
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users1"].get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users1"].get())->setString("Waiting players");
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users1"].get())->setCharacterSize(35);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users1"].get())->setFillColor(sf::Color::White);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users1"].get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users1"].get())->setPosition(sf::Vector2f(550, 230));

    modDrawables.at(sceneName::ROOM).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("status1", std::make_unique<sf::Sprite>()));
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::ROOM)["status1"].get())->setTexture(*loadedTextures["waiting"]);
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::ROOM)["status1"].get())->setOrigin(sf::Vector2f(16, 16));
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::ROOM)["status1"].get())->setPosition(sf::Vector2f(1060, 250));

    modDrawables.at(sceneName::ROOM).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("users2", std::make_unique<sf::Text>()));
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users2"].get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users2"].get())->setString("Waiting players");
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users2"].get())->setCharacterSize(35);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users2"].get())->setFillColor(sf::Color::White);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users2"].get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users2"].get())->setPosition(sf::Vector2f(550, 330));

    modDrawables.at(sceneName::ROOM).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("status2", std::make_unique<sf::Sprite>()));
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::ROOM)["status2"].get())->setTexture(*loadedTextures["waiting"]);
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::ROOM)["status2"].get())->setOrigin(sf::Vector2f(16, 16));
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::ROOM)["status2"].get())->setPosition(sf::Vector2f(1060, 350));

    modDrawables.at(sceneName::ROOM).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("users3", std::make_unique<sf::Text>()));
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users3"].get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users3"].get())->setString("Waiting players");
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users3"].get())->setCharacterSize(35);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users3"].get())->setFillColor(sf::Color::White);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users3"].get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users3"].get())->setPosition(sf::Vector2f(550, 430));

    modDrawables.at(sceneName::ROOM).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("status3", std::make_unique<sf::Sprite>()));
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::ROOM)["status3"].get())->setTexture(*loadedTextures["waiting"]);
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::ROOM)["status3"].get())->setOrigin(sf::Vector2f(16, 16));
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::ROOM)["status3"].get())->setPosition(sf::Vector2f(1060, 450));

    modDrawables.at(sceneName::ROOM).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("users4", std::make_unique<sf::Text>()));
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users4"].get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users4"].get())->setString("Waiting players");
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users4"].get())->setCharacterSize(35);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users4"].get())->setFillColor(sf::Color::White);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users4"].get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(modDrawables.at(sceneName::ROOM)["users4"].get())->setPosition(sf::Vector2f(550, 530));

    modDrawables.at(sceneName::ROOM).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("status4", std::make_unique<sf::Sprite>()));
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::ROOM)["status4"].get())->setTexture(*loadedTextures["waiting"]);
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::ROOM)["status4"].get())->setOrigin(sf::Vector2f(16, 16));
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::ROOM)["status4"].get())->setPosition(sf::Vector2f(1060, 550));
}