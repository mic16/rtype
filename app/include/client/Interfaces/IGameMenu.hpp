/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** IGameMenu
*/

#ifndef IGAMEMENU_HPP_
#define IGAMEMENU_HPP_

#include "SFML/Graphics.hpp"
#include "client/Class/GameEntities/GameEntities.hpp"

enum sceneName { LOGIN, MENU, CREATE, JOIN, ROOM, GAME };

enum menuButton { B_CREATE, B_JOIN };

class IGameMenu {
    public:
        virtual int run() = 0;

        virtual void draw() = 0;
        virtual bool isOpen() = 0;

        virtual bool isNameValid(const std::string &name) = 0;
        virtual const std::string &getUsername() = 0;

        virtual void handleEvents() = 0;
        virtual void handleTextEntered() = 0;
        virtual void handleKeyReleased() = 0;

        virtual void handleDisplay() = 0;
        virtual void tryLogIn() = 0;
        virtual void tryCreateRoom() = 0;
        virtual void tryJoinRoom() = 0;

        virtual const sceneName getScene() = 0;
        virtual void setScene(const sceneName sc_name) = 0;
        virtual const std::unique_ptr<sf::Drawable> &getDrawable(sceneName scene, const std::string &key) = 0;
        virtual void setDrawableTextStr(sceneName scene, const std::string &key, const std::string &text) = 0;
        virtual void setDrawableTextColor(sceneName scene, const std::string &key, const sf::Color &color) = 0;
        virtual void setDrawableSpriteTexture(sceneName scene, const std::string &key, const std::string &texture) = 0;

        virtual std::shared_ptr<GameEntities> getGameEntities() = 0;
};

#endif /* !IGAMEMENU_HPP_ */