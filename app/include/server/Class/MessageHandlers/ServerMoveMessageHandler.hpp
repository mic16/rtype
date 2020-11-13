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

        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !SERVERMOVEMESSAGEHANDLER_HPP_ */
