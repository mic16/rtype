/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** RTypeServer
*/

#ifndef RTYPESERVER_HPP_
#define RTYPESERVER_HPP_

#include "server/Class/AServer/AServer.hpp"
#include "server/Class/Client/Client.hpp"

class RTypeServer : public AServer {
    public:
        RTypeServer();
        ~RTypeServer();

        void work() override;

        unsigned int prepareNewClient();

        void handleConnection();
        void handleClient(const unsigned int client_id);

    private:
        std::map<unsigned int, std::unique_ptr<Client>> clients;
};

#endif /* !RTYPESERVER_HPP_ */
