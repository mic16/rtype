/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** initSprites
*/

#include "client/Class/GameMenu/GameMenu.hpp"

void GameMenu::initDrawables()
{
    fixedDrawables.insert(std::pair<sceneName, std::vector<std::unique_ptr<sf::Drawable>>>(sceneName::LOGIN, std::vector<std::unique_ptr<sf::Drawable>>()));
    modDrawables.insert(std::pair<sceneName, std::map<std::string, std::unique_ptr<sf::Drawable>>>(sceneName::LOGIN, std::map<std::string, std::unique_ptr<sf::Drawable>>()));

    fixedDrawables.insert(std::pair<sceneName, std::vector<std::unique_ptr<sf::Drawable>>>(sceneName::MENU, std::vector<std::unique_ptr<sf::Drawable>>()));
    modDrawables.insert(std::pair<sceneName, std::map<std::string, std::unique_ptr<sf::Drawable>>>(sceneName::MENU, std::map<std::string, std::unique_ptr<sf::Drawable>>()));

    fixedDrawables.insert(std::pair<sceneName, std::vector<std::unique_ptr<sf::Drawable>>>(sceneName::CREATE, std::vector<std::unique_ptr<sf::Drawable>>()));
    modDrawables.insert(std::pair<sceneName, std::map<std::string, std::unique_ptr<sf::Drawable>>>(sceneName::CREATE, std::map<std::string, std::unique_ptr<sf::Drawable>>()));

    fixedDrawables.insert(std::pair<sceneName, std::vector<std::unique_ptr<sf::Drawable>>>(sceneName::JOIN, std::vector<std::unique_ptr<sf::Drawable>>()));
    modDrawables.insert(std::pair<sceneName, std::map<std::string, std::unique_ptr<sf::Drawable>>>(sceneName::JOIN, std::map<std::string, std::unique_ptr<sf::Drawable>>()));

    fixedDrawables.insert(std::pair<sceneName, std::vector<std::unique_ptr<sf::Drawable>>>(sceneName::ROOM, std::vector<std::unique_ptr<sf::Drawable>>()));
    modDrawables.insert(std::pair<sceneName, std::map<std::string, std::unique_ptr<sf::Drawable>>>(sceneName::ROOM, std::map<std::string, std::unique_ptr<sf::Drawable>>()));

    fixedDrawables.insert(std::pair<sceneName, std::vector<std::unique_ptr<sf::Drawable>>>(sceneName::GAME, std::vector<std::unique_ptr<sf::Drawable>>()));
    modDrawables.insert(std::pair<sceneName, std::map<std::string, std::unique_ptr<sf::Drawable>>>(sceneName::GAME, std::map<std::string, std::unique_ptr<sf::Drawable>>()));

    initFixedLoginDrawables();
    initModLoginDrawables();

    initFixedMenuDrawables();
    initModMenuDrawables();

    initFixedCreateDrawables();
    initModCreateDrawables();

    initFixedJoinDrawables();
    initModJoinDrawables();

    initFixedRoomDrawables();
    initModRoomDrawables();
}