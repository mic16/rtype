/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** SpawnMessageHandler
*/

#ifndef SERVERSPAWNMESSAGEHANDLER_HPP_
#define SERVERSPAWNMESSAGEHANDLER_HPP_


#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/SpawnPacket.hpp"

class ServerSpawnMessageHandler : public AMessageHandler<SpawnPacket> {
    public:
        ServerSpawnMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ServerSpawnMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, SpawnPacket &packet) {

        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !SERVERSPAWNMESSAGEHANDLER_HPP_ */
