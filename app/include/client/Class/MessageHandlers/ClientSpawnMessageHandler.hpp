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

#include "shared/Synchronizer/Synchronizer.hpp"

class ClientSpawnMessageHandler : public AMessageHandler<SpawnPacket> {
    public:
        ClientSpawnMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ClientSpawnMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, SpawnPacket &packet) {
            auto &vector = synchronizer.getDoubleQueue().getWriteVector();

            vector->emplace_back(new SpawnPacket(packet));
            synchronizer.getDoubleQueue().update();
        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !CLIENTSPAWNMESSAGEHANDLER_HPP_ */
