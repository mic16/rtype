/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** game
*/

#include "client/Class/GameMenu/GameMenu.hpp"

void GameMenu::tryStartGame()
{
    buffer.clear();

    buffer.writeUInt(sizeof(int) + sizeof(unsigned int) + roomname.length() + 1);
    buffer.writeInt(req::Type::StartGame);
    buffer.writeCharBuffer(roomname.c_str());

    std::cout << "TryStartGame: sending " << buffer.getSize() << " bytes." << std::endl;
    client->sendData(buffer.flush(), buffer.getSize());
}

void GameMenu::initFixedGameDrawables()
{

}

void GameMenu::initModGameDrawables()
{
    modDrawables.at(sceneName::GAME).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("player", std::make_unique<sf::Sprite>()));
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::GAME)["player"].get())->setTexture(*loadedTextures["players"]);
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::GAME)["player"].get())->setOrigin(sf::Vector2f(16, 16));
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::GAME)["player"].get())->setPosition(sf::Vector2f(200, 200));

    modDrawables.at(sceneName::GAME).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("enemy", std::make_unique<sf::Sprite>()));
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::GAME)["enemy"].get())->setTexture(*loadedTextures["enemy1"]);
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::GAME)["enemy"].get())->setOrigin(sf::Vector2f(0, 0));
    dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::GAME)["enemy"].get())->setPosition(sf::Vector2f(400, 200));

    sf::Sprite *player1Sprite = new sf::Sprite();
    player1Sprite->setTexture(*loadedTextures["players"]);
    spriteManager.pushSprite(EntityType::PLAYER1, player1Sprite);

    sf::Sprite *enemy1Sprite = new sf::Sprite();
    enemy1Sprite->setTexture(*loadedTextures["enemy1"]);
    spriteManager.pushSprite(EntityType::ENEMY1, enemy1Sprite);
}