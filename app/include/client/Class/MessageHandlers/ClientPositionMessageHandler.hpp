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

class ClientPositionMessageHandler : public AMessageHandler<PositionPacket> {
    public:
        ClientPositionMessageHandler() {}
        ~ClientPositionMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, PositionPacket &packet) {

        }

    protected:
    private:
};

#endif /* !CLIENTPOSITIONMESSAGEHANDLER_HPP */
