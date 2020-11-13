/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameMenu
*/

#ifndef GAMEMENU_HPP_
#define GAMEMENU_HPP_

#include <memory>
#include <thread>
#include <mutex>
#include <map>
#include <cctype>

#include "client/Class/TCPClient/TCPClient.hpp"
#include "client/Class/ResourceLoader/ResourceLoader.hpp"
#include "client/Class/Exceptions/EFinished.hpp"
#include "lib/ByteBuffer/ByteBuffer.hpp"
#include "client/Class/GameEntities/GameEntities.hpp"
#include "client/Class/UDPClient/UDPClient.hpp"

#include "lib/Network/NetworkHandler.hpp"
#include "shared/Synchronizer/Synchronizer.hpp"
#include "shared/Packet/MovePacket.hpp"

#define LAST_FIXED_SPRITE(sceneName) fixedDrawables.at(sceneName)[fixedDrawables.at(sceneName).size() - 1]

class GameMenu : public IGameMenu {
    public:
        GameMenu();
        ~GameMenu();

        int run();

        void draw();
        void draw(float deltaTime);
        bool isOpen();

        bool isNameValid(const std::string &name);
        const std::string &getUsername();

        void handleEvents();
        void handleTextEntered();
        void handleKeyReleased();
        void handleKeyPressed();

        void handleDisplay();
        void tryLogIn();
        void tryCreateRoom();
        void tryJoinRoom();
        void tryChangeUserStatus();
        void tryStartGame();
        void disconnectRoom();

        const sceneName getScene();
        void setScene(const sceneName sc_name);
        const std::unique_ptr<sf::Drawable> &getDrawable(sceneName scene, const std::string &key);
        void setDrawableTextStr(sceneName scene, const std::string &key, const std::string &text);
        void setDrawableTextColor(sceneName scene, const std::string &key, const sf::Color &color);
        void setDrawableSpriteTexture(sceneName scene, const std::string &key, const std::string &texture);

        GameEntities *getGameEntities() { return (&gameEntities); };

        NetworkHandler &getNetworkHandler() {
            return networkHandler;
        }

    private:
        void initDrawables();

        void initFixedLoginDrawables();
        void initModLoginDrawables();

        void initFixedMenuDrawables();
        void initModMenuDrawables();

        void initFixedCreateDrawables();
        void initModCreateDrawables();

        void initFixedJoinDrawables();
        void initModJoinDrawables();

        void initFixedRoomDrawables();
        void initModRoomDrawables();

        void initFixedGameDrawables();
        void initModGameDrawables();

        Synchronizer synchronizer;
        NetworkHandler networkHandler = {1024};

        sceneName scene;
        std::unique_ptr<TCPClient> client;
        std::string username;
        std::string roomname;
        std::string users[4];

        ResourceLoader loadedTextures;
        std::map<sceneName, std::vector<std::unique_ptr<sf::Drawable>>> fixedDrawables;
        std::map<sceneName, std::map<std::string, std::unique_ptr<sf::Drawable>>> modDrawables;
        sf::RenderWindow window;
        sf::Event event;
        sf::Font mainFont;

        std::unique_ptr<std::thread> displayThread;

        ByteBuffer buffer;
        menuButton actualButton;

        std::mutex scene_mutex;
        std::mutex drawables_mutex;
        std::mutex window_mutex;

        GameEntities gameEntities;
        bool isDirectionMaintained[4];

        size_t playerId;
};

static const std::string menuButtons[] = {
    "createRoom",
    "joinRoom"
};

#endif /* !GAMEMENU_HPP_ */