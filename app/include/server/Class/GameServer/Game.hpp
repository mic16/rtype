/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <chrono>

#include "server/Class/GameServer/GameServer.hpp"
#include "server/Class/Ladder/Ladder.hpp"
#include "lib/Network/NetworkHandler.hpp"
#include "ECS/ECS.hpp"
#include "API/IExtension.hpp"

class Game {
    public:
        Game();
        ~Game();

        void loadExtensions(std::vector<std::unique_ptr<IExtension>> &extensions);
        void compile();
        void update();

        const server_info_t setGameServer();
        void startGame();
        Ladder &getLobby();

    private:
        std::chrono::high_resolution_clock::time_point lastTime;
        ECS ecs;
        NetworkHandler networkHandler = {1024};
        Ladder lobby;
        GameServer gameServer;
};

#endif /* !GAME_HPP_ */
