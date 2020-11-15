/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** IGameMenu
*/

#ifndef IGAMEMENU_HPP_
#define IGAMEMENU_HPP_

#include "SFML/Graphics.hpp"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include "client/Class/GameEntities/GameEntities.hpp"
#include "lib/Network/NetworkHandler.hpp"
#include "client/Interfaces/IGame.hpp"

enum sceneName { LOGIN, MENU, CREATE, JOIN, ROOM, GAME, END };

enum menuButton { B_CREATE, B_JOIN };

class IGameMenu : public IGame {
    public:
        virtual int run(const std::string &addr) = 0;

        virtual void draw() = 0;
        virtual void draw(float deltaTime) = 0;
        virtual bool isOpen() = 0;

        virtual bool isNameValid(const std::string &name) = 0;
        virtual const std::string &getUsername() = 0;

        virtual void handleEvents() = 0;
        virtual void handleTextEntered() = 0;
        virtual void handleKeyReleased() = 0;

        virtual const std::string &getAddress() const = 0;
        virtual void handleDisplay() = 0;
        virtual void tryLogIn() = 0;
        virtual void tryCreateRoom() = 0;
        virtual void tryJoinRoom() = 0;
        virtual void tryQuit() = 0;

        virtual const sceneName getScene() = 0;
        virtual void setScene(const sceneName sc_name) = 0;
        virtual const std::unique_ptr<sf::Drawable> &getDrawable(sceneName scene, const std::string &key) = 0;
        virtual void setDrawableTextStr(sceneName scene, const std::string &key, const std::string &text) = 0;
        virtual void setDrawableTextColor(sceneName scene, const std::string &key, const sf::Color &color) = 0;
        virtual void setDrawableSpriteTexture(sceneName scene, const std::string &key, const std::string &texture) = 0;

        virtual GameEntities *getGameEntities() = 0;
        virtual NetworkHandler &getNetworkHandler() = 0;

        virtual void setPlayerID(size_t id) = 0;
        virtual size_t getPlayerID() = 0;
};

#endif /* !IGAMEMENU_HPP_ */