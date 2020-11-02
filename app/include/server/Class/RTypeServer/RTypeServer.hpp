/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** RTypeServer
*/

#ifndef RTYPESERVER_HPP_
#define RTYPESERVER_HPP_

#include "server/Class/TCPServer/TCPServer.hpp"
#include "server/Class/Client/Client.hpp"
#include "server/Class/GameServer/GameServer.hpp"

class RTypeServer : public TCPServer {
    public:
        RTypeServer();
        ~RTypeServer();

        void work() override;

        unsigned int prepareNewClient();

        bool isClientConnected(const unsigned int client_id);

        bool handleConnection();
        bool handleClient(const unsigned int client_id);

        bool disconnectClient(const unsigned int client_id);

        const std::map<unsigned int, std::unique_ptr<Client>> &getClients() const;
    private:
        std::map<unsigned int, std::unique_ptr<Client>> clients;
};

#endif /* !RTYPESERVER_HPP_ */
