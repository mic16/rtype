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

#include "shared/Synchronizer/Synchronizer.hpp"

class ClientFireMessageHandler : public AMessageHandler<FirePacket> {
    public:
        ClientFireMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ClientFireMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, FirePacket &packet) {

        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !CLIENTFIREMESSAGEHANDLER_HPP */
