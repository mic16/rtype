/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** PositionPacket
*/

#ifndef CLIENTPOSITIONMESSAGEHANDLER_HPP
#define CLIENTPOSITIONMESSAGEHANDLER_HPP

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/PositionPacket.hpp"

#include "shared/Synchronizer/Synchronizer.hpp"

class ClientPositionMessageHandler : public AMessageHandler<PositionPacket> {
    public:
        ClientPositionMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ClientPositionMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, PositionPacket &packet) {
            auto &writeMap = synchronizer.getDoubleMap().getWriteMap();

            if (writeMap->find(packet.getEntityID()) == writeMap->end()) {
                writeMap->insert({packet.getEntityID(), PacketData()});
            }
            auto &packetData = writeMap->at(packet.getEntityID());

            packetData.x = packet.getX();
            packetData.y = packet.getY();
            packetData.moveChanged = true;
            packetData.entityType = packet.getEntityType();

            // if (readMap->find(entityID->id) == readMap->end()) {
            //     if (spawnpacket->isPlayer()) {
            //         playerGenerator.instanciate(1,
            //         Position{spawnpacket->getX(), spawnpacket->getY()},
            //         EntityID{spawnpacket->getEntityID()},
            //         animationManager.getAnimation(spawnpacket->getEntityType()),
            //         Drawable{true, spriteManager.getSprite(spawnpacket->getEntityType())});
            //     } else {
            //         entityGenerator.instanciate(1,
            //         Position{spawnpacket->getX(), spawnpacket->getY()},
            //         EntityID{spawnpacket->getEntityID()},
            //         animationManager.getAnimation(spawnpacket->getEntityType()),
            //         Drawable{true, spriteManager.getSprite(spawnpacket->getEntityType())}
            //         );
            //     }
            // }

            synchronizer.update();
        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !CLIENTPOSITIONMESSAGEHANDLER_HPP */
