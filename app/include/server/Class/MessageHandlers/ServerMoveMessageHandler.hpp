/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** MovePacket
*/

#ifndef SERVERMOVEMESSAGEHANDLER_HPP_
#define SERVERMOVEMESSAGEHANDLER_HPP_

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/MovePacket.hpp"

#include "shared/Synchronizer/Synchronizer.hpp"

class ServerMoveMessageHandler : public AMessageHandler<MovePacket> {
    public:
        ServerMoveMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ServerMoveMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, MovePacket &packet) {
            size_t entityID = handler.getRelatedEntityFromNetwork(client);

            auto &writeMap = synchronizer.getDoubleMap().getWriteMap();

            if (writeMap->find(entityID) == writeMap->end()) {
                writeMap->insert({entityID, PacketData()});
            }

            PacketData &data = writeMap->at(entityID);
            if (packet.getDirectionX() < 0) {
                data.dirX = -1;
            } else if (packet.getDirectionX() > 0) {
                data.dirX = 1;
            } else {
                data.dirX = 0;
            }

            if (packet.getDirectionY() < 0) {
                data.dirY = -1;
            } else if (packet.getDirectionY() > 0) {
                data.dirY = 1;
            } else {
                data.dirY = 0;
            }

            data.moveChanged = true;

            synchronizer.update();
        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !SERVERMOVEMESSAGEHANDLER_HPP_ */
