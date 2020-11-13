/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** PositionPacket
*/

#ifndef SERVERPOSITIONMESSAGEHANDLER_HPP
#define SERVERPOSITIONMESSAGEHANDLER_HPP

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/PositionPacket.hpp"

class ServerPositionMessageHandler : public AMessageHandler<PositionPacket> {
    public:
        ServerPositionMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ServerPositionMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, PositionPacket &packet) {

        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !SERVERPOSITIONMESSAGEHANDLER_HPP */
