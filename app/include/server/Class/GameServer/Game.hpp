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
#include "shared/Packet/PingPacket.hpp"

#include "shared/Components/Components.hpp"
#include "shared/Synchronizer/Synchronizer.hpp"

#include "shared/Structs/EntityHitboxs.hpp"
#include "shared/Structs/EntityType.hpp"

#define AVAILABLE_PORTS 8
#define BEGIN_PORT 3333

class Game : public Synchronizer {
    public:
        Game(const std::string &name);
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

        static double getMapWidth() {return 1600; }
        static double getMapHeight() {return 800; }
        size_t getNextEntityID();

        void stopRunning() { m_isGaming = false; }
        const bool isGaming() const { return m_isGaming; }

        static unsigned int GenPortValue() {
            static unsigned int port = BEGIN_PORT;
            port += 1;

            return port;
        };

        void close() {
            gameServer.close();
        }

        const std::string &getRoomName() const { return roomname; }
    private:
        std::string roomname;
        std::chrono::high_resolution_clock::time_point lastTime;
        std::chrono::high_resolution_clock::time_point lastRequestStatus;
        ECS ecs;
        NetworkHandler networkHandler = {512};
        Ladder lobby;
        GameServer gameServer;
        bool m_isGaming = true;

        unsigned short playerID = 1;
        size_t entityId = 0;
        bool canLogin = true;
        std::chrono::high_resolution_clock::time_point start;
        std::chrono::high_resolution_clock::time_point t1;
};

#endif /* !GAME_HPP_ */
