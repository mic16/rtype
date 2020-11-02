/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameServer
*/

#ifndef GAMESERVER_HPP_
#define GAMESERVER_HPP_

#include "lib/Server/UDPServer/UDPServer.hpp"

class GameServer : public UDPServer {
    public:
        GameServer();
        ~GameServer();

        void work() override;

        unsigned int prepareNewClient();

        bool isClientConnected(const unsigned int client_id);

        bool handleConnection();
        bool handleClient(const unsigned int client_id);

        bool disconnectClient(const unsigned int client_id);

        const std::map<unsigned int, boost::asio::ip::udp::endpoint> &getClients() const;
    private:
        std::map<unsigned int, boost::asio::ip::udp::endpoint> clients;
};

#endif /* !GAMESERVER_HPP_ */