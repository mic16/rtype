/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** ClientPingMessageHandler
*/

#ifndef CLIENTPINGMESSAGEHANDLER_HPP_
#define CLIENTPINGMESSAGEHANDLER_HPP_

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/PingPacket.hpp"

#include "shared/Synchronizer/Synchronizer.hpp"

class ClientPingMessageHandler : public AMessageHandler<PingPacket> {
    public:
        ClientPingMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ClientPingMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, PingPacket &packet) {
            handler.broadcast(packet);
            synchronizer.update();
        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !CLIENTPINGMESSAGEHANDLER_HPP_ */
