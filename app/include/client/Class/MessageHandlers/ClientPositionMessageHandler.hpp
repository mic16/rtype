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

        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !CLIENTPOSITIONMESSAGEHANDLER_HPP */
