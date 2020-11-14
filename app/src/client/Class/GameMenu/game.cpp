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
    // modDrawables.at(sceneName::GAME).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("player", std::make_unique<sf::Sprite>()));
    // dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::GAME)["player"].get())->setTexture(*loadedTextures["players"]);
    // dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::GAME)["player"].get())->setOrigin(sf::Vector2f(0, 0));

    // modDrawables.at(sceneName::GAME).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("enemy", std::make_unique<sf::Sprite>()));
    // dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::GAME)["enemy"].get())->setTexture(*loadedTextures["enemy1"]);
    // dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::GAME)["enemy"].get())->setOrigin(sf::Vector2f(0, 0));

    // modDrawables.at(sceneName::GAME).insert(std::pair<std::string, std::unique_ptr<sf::Drawable>>("projectile", std::make_unique<sf::Sprite>()));
    // dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::GAME)["projectile"].get())->setTexture(*loadedTextures["projectile1"]);
    // dynamic_cast<sf::Sprite *>(modDrawables.at(sceneName::GAME)["projectile"].get())->setOrigin(sf::Vector2f(0, 0));

    sf::Sprite *player1Sprite = new sf::Sprite();
    player1Sprite->setTexture(*loadedTextures["players"]);
    spriteManager.pushSprite(EntityType::PLAYER1, player1Sprite);

    sf::Sprite *enemy1Sprite = new sf::Sprite();
    enemy1Sprite->setTexture(*loadedTextures["enemy1"]);
    spriteManager.pushSprite(EntityType::ENEMY1, enemy1Sprite);

    sf::Sprite *enemy2Sprite = new sf::Sprite();
    enemy2Sprite->setTexture(*loadedTextures["enemy2"]);
    spriteManager.pushSprite(EntityType::ENEMY2, enemy2Sprite);

    sf::Sprite *enemy3Sprite = new sf::Sprite();
    enemy3Sprite->setTexture(*loadedTextures["enemy3"]);
    spriteManager.pushSprite(EntityType::ENEMY3, enemy3Sprite);

    sf::Sprite *enemy4Sprite = new sf::Sprite();
    enemy4Sprite->setTexture(*loadedTextures["enemy4"]);
    spriteManager.pushSprite(EntityType::ENEMY4, enemy4Sprite);

    sf::Sprite *enemy5Sprite = new sf::Sprite();
    enemy5Sprite->setTexture(*loadedTextures["enemy5"]);
    spriteManager.pushSprite(EntityType::ENEMY5, enemy5Sprite);

    sf::Sprite *enemy6Sprite = new sf::Sprite();
    enemy6Sprite->setTexture(*loadedTextures["enemy6"]);
    spriteManager.pushSprite(EntityType::ENEMY6, enemy6Sprite);

    sf::Sprite *projectile1Sprite = new sf::Sprite();
    projectile1Sprite->setTexture(*loadedTextures["projectile1"]);
    spriteManager.pushSprite(EntityType::PROJECTILE1, projectile1Sprite);

    Animation *player1Animation = new Animation{sf::Vector2u(5, 5), sf::Vector2u(2, 0), sf::Vector2u(2, 0), 0, 0.05f, 
        sf::IntRect(0, 0, loadedTextures["players"].get()->getSize().x / 5, loadedTextures["players"].get()->getSize().y / 5), false};
    animationManager.pushAnimation(EntityType::PLAYER1, player1Animation);

    Animation *enemy1Animation = new Animation{sf::Vector2u(7, 1), sf::Vector2u(0, 0), sf::Vector2u(0, 0), 0, 0.05f, 
        sf::IntRect(0, 0, loadedTextures["enemy1"].get()->getSize().x / 7, loadedTextures["enemy1"].get()->getSize().y / 1), false};
    animationManager.pushAnimation(EntityType::ENEMY1, enemy1Animation);

    Animation *enemy2Animation = new Animation{sf::Vector2u(8, 1), sf::Vector2u(0, 0), sf::Vector2u(0, 0), 0, 0.05f, 
        sf::IntRect(0, 0, loadedTextures["enemy2"].get()->getSize().x / 8, loadedTextures["enemy2"].get()->getSize().y / 1), false};
    animationManager.pushAnimation(EntityType::ENEMY2, enemy2Animation);

    Animation *enemy3Animation = new Animation{sf::Vector2u(5, 1), sf::Vector2u(0, 0), sf::Vector2u(0, 0), 0, 0.05f, 
        sf::IntRect(0, 0, loadedTextures["enemy3"].get()->getSize().x / 5, loadedTextures["enemy3"].get()->getSize().y / 1), false};
    animationManager.pushAnimation(EntityType::ENEMY3, enemy3Animation);

    Animation *enemy4Animation = new Animation{sf::Vector2u(3, 2), sf::Vector2u(0, 0), sf::Vector2u(0, 0), 0, 0.05f, 
        sf::IntRect(0, 0, loadedTextures["enemy4"].get()->getSize().x / 3, loadedTextures["enemy4"].get()->getSize().y / 2), false};
    animationManager.pushAnimation(EntityType::ENEMY4, enemy4Animation);

    Animation *enemy5Animation = new Animation{sf::Vector2u(3, 1), sf::Vector2u(0, 0), sf::Vector2u(0, 0), 0, 0.05f, 
        sf::IntRect(0, 0, loadedTextures["enemy5"].get()->getSize().x / 3, loadedTextures["enemy5"].get()->getSize().y / 1), false};
    animationManager.pushAnimation(EntityType::ENEMY5, enemy5Animation);

    Animation *enemy6Animation = new Animation{sf::Vector2u(3, 1), sf::Vector2u(0, 0), sf::Vector2u(0, 0), 0, 0.05f, 
        sf::IntRect(0, 0, loadedTextures["enemy6"].get()->getSize().x / 3, loadedTextures["enemy6"].get()->getSize().y / 1), false};
    animationManager.pushAnimation(EntityType::ENEMY6, enemy6Animation);

    Animation *projectile1Animation = new Animation{sf::Vector2u(2, 1), sf::Vector2u(0, 0), sf::Vector2u(0, 0), 0, 0.05f, 
        sf::IntRect(0, 0, loadedTextures["projectile1"].get()->getSize().x / 2, loadedTextures["projectile1"].get()->getSize().y / 1), false};
    animationManager.pushAnimation(EntityType::PROJECTILE1, projectile1Animation);

    Animation *projectile2Animation = new Animation{sf::Vector2u(2, 1), sf::Vector2u(0, 0), sf::Vector2u(0, 0), 0, 0.05f, 
        sf::IntRect(0, 0, loadedTextures["projectile2"].get()->getSize().x / 2, loadedTextures["projectile2"].get()->getSize().y / 1), false};
    animationManager.pushAnimation(EntityType::PROJECTILE2, projectile2Animation);

    Animation *projectile3Animation = new Animation{sf::Vector2u(4, 1), sf::Vector2u(0, 0), sf::Vector2u(0, 0), 0, 0.05f, 
        sf::IntRect(0, 0, loadedTextures["projectile3"].get()->getSize().x / 4, loadedTextures["projectile3"].get()->getSize().y / 1), false};
    animationManager.pushAnimation(EntityType::PROJECTILE3, projectile3Animation);
}