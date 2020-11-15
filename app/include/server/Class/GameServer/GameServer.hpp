/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameServer
*/

#ifndef GAMESERVER_HPP_
#define GAMESERVER_HPP_

#include "lib/Server/UDPServer/UDPServer.hpp"
#include "server/Class/UDPClient/UDPClient.hpp"
#include "lib/Network/NetworkHandler.hpp"
#include "shared/Synchronizer/Synchronizer.hpp"

#include <memory>

typedef struct server_info_s {
    std::string address;
    unsigned int port;
} server_info_t;

class GameServer : public UDPServer {
    public:
        GameServer(Synchronizer &synchronizer, NetworkHandler &netwHandler);
        ~GameServer();

        void close() {
            ioService.stop();
        }

        void work() override;

        bool isClientConnected(const unsigned int client_id);

        bool handleConnection();

        bool disconnectClient(const unsigned int client_id);

        const UDPClient &getClients() const;
    private:
        UDPClient client;
        std::map<std::string, UDPClient *> players;
        NetworkHandler &networkHandler;
        Synchronizer &synchronizer;
};

#endif /* !GAMESERVER_HPP_ */