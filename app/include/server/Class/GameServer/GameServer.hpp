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
    protected:
    private:
};

#endif /* !GAMESERVER_HPP_ */