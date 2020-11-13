/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** DeathMessageHandler
*/

#ifndef CLIENTDEATHMESSAGEHANDLER_HPP_
#define CLIENTDEATHMESSAGEHANDLER_HPP_

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/DeathPacket.hpp"

#include "shared/Synchronizer/Synchronizer.hpp"

class ClientDeathMessageHandler : public AMessageHandler<DeathPacket> {
    public:
        ClientDeathMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ClientDeathMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, DeathPacket &packet) {

        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !CLIENTDEATHMESSAGEHANDLER_HPP_ */
