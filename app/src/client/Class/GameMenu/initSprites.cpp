/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** initSprites
*/

#include "client/Class/GameMenu/GameMenu.hpp"

void GameMenu::initFixedSprites()
{
    fixedSprites.insert(std::pair<sceneName, std::vector<std::unique_ptr<sf::Drawable>>>(sceneName::LOGIN, std::vector<std::unique_ptr<sf::Drawable>>()));

    initFixedLoginSprites();
}

void GameMenu::initFixedLoginSprites()
{
    fixedSprites.at(sceneName::LOGIN).push_back(std::make_unique<sf::Sprite>());
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setTexture(*loadedTextures["background"]);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setOrigin(sf::Vector2f(960, 480));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setPosition(sf::Vector2f(800, 400));

    fixedSprites.at(sceneName::LOGIN).push_back(std::make_unique<sf::Text>());
    mainFont.loadFromFile("./app/assets/fonts/pixelart.ttf");
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setString("Enter your Username:");
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setCharacterSize(40);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setFillColor(sf::Color::White);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setPosition(sf::Vector2f(520, 280));

    fixedSprites.at(sceneName::LOGIN).push_back(std::make_unique<sf::Sprite>());
    sf::Texture backInput;
    backInput.create(600, 80);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setTexture(backInput);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setColor(sf::Color::Black);
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setOrigin(sf::Vector2f(300, 40));
    dynamic_cast<sf::Sprite *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setPosition(sf::Vector2f(800, 400));

    fixedSprites.at(sceneName::LOGIN).push_back(std::make_unique<sf::Text>());
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setFont(mainFont);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setString("username");
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setCharacterSize(35);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setFillColor(sf::Color::White);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setStyle(sf::Text::Bold);
    dynamic_cast<sf::Text *>(LAST_FIXED_SPRITE(sceneName::LOGIN).get())->setPosition(sf::Vector2f(520, 375));
}