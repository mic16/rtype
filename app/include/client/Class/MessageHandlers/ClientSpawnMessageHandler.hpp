/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** SpawnMessageHandler
*/

#ifndef CLIENTSPAWNMESSAGEHANDLER_HPP_
#define CLIENTSPAWNMESSAGEHANDLER_HPP_

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/SpawnPacket.hpp"

class ClientSpawnMessageHandler : public AMessageHandler<SpawnPacket> {
    public:
        ClientSpawnMessageHandler() {}
        ~ClientSpawnMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, SpawnPacket &packet) {

        }

    protected:
    private:
};

#endif /* !CLIENTSPAWNMESSAGEHANDLER_HPP_ */
