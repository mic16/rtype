/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** FirePacket
*/

#ifndef CLIENTFIREMESSAGEHANDLER_HPP
#define CLIENTFIREMESSAGEHANDLER_HPP

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/FirePacket.hpp"

class ClientFireMessageHandler : public AMessageHandler<FirePacket> {
    public:
        ClientFireMessageHandler() {}
        ~ClientFireMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, FirePacket &packet) {

        }

    protected:
    private:
};

#endif /* !CLIENTFIREMESSAGEHANDLER_HPP */
