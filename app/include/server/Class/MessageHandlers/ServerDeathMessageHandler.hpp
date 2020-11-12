/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** DeathMessageHandler
*/

#ifndef SERVERDEATHMESSAGEHANDLER_HPP_
#define SERVERDEATHMESSAGEHANDLER_HPP_

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/DeathPacket.hpp"

class ServerDeathMessageHandler : public AMessageHandler<DeathPacket> {
    public:
        ServerDeathMessageHandler() {}
        ~ServerDeathMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, DeathPacket &packet) {

        }

    protected:
    private:
};

#endif /* !SERVERDEATHMESSAGEHANDLER_HPP_ */
