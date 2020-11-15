/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** FirePacket
*/

#ifndef SERVERFIREMESSAGEHANDLER_HPP
#define SERVERFIREMESSAGEHANDLER_HPP

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/FirePacket.hpp"

#include "shared/Synchronizer/Synchronizer.hpp"

class ServerFireMessageHandler : public AMessageHandler<FirePacket> {
    public:
        ServerFireMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ServerFireMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, FirePacket &packet) {
            auto &writeMap = synchronizer.getDoubleMap().getWriteMap();

            size_t entityID = handler.getEntityIDFromNetworkClient(client);
            if (writeMap->find(entityID) == writeMap->end()) {
                writeMap->insert({entityID, PacketData()});
            }

            PacketData &data = writeMap->at(entityID);

            data.isFiring = packet.isHolding();
            data.fireChanged = true;

            synchronizer.update();
        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !SERVERFIREMESSAGEHANDLER_HPP */
