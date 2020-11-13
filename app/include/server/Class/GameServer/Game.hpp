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
#include "ECS/ECS.hpp"
#include "API/IExtension.hpp"

#include "shared/Packet/DeathPacket.hpp"
#include "shared/Packet/PositionPacket.hpp"
#include "shared/Packet/SpawnPacket.hpp"
#include "shared/Packet/DamagePacket.hpp"

#include "shared/Components/Components.hpp"
#include "shared/Synchronizer/Synchronizer.hpp"

class Game : public Synchronizer {
    public:
        Game();
        ~Game();

        void init();
        void loadExtensions(std::vector<std::unique_ptr<IExtension>> &extensions);
        void compile();
        void update();

        const server_info_t setGameServer();
        void startGame();
        Ladder &getLobby();

        ECS &getECS();
        NetworkHandler &getNetworkHandler();

        static double getMapWidth() {return 2000; }
        static double getMapHeight() {return 2000/3; }

    private:
        std::chrono::high_resolution_clock::time_point lastTime;
        ECS ecs;
        NetworkHandler networkHandler = {1024};
        Ladder lobby;
        GameServer gameServer;
        DoubleQueue<IPacket> doubleQueue;
        DoubleHashmap<size_t, IPacket> doubleMap;
};

#endif /* !GAME_HPP_ */
