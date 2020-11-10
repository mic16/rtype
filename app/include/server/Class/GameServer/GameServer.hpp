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

#include <memory>

class GameServer : public UDPServer {
    public:
        GameServer();
        ~GameServer();

        void work() override;

        bool isClientConnected(const unsigned int client_id);

        bool handleConnection();

        bool disconnectClient(const unsigned int client_id);

        const std::unique_ptr<UDPClient> &getClients() const;
    private:
        std::unique_ptr<UDPClient> client;
        std::map<std::string, std::unique_ptr<UDPClient>> players;
};

#endif /* !GAMESERVER_HPP_ */