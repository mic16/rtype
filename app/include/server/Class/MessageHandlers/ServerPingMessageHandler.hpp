/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** ServerPingMessageHandler
*/

#ifndef SERVERPINGMESSAGEHANDLER_HPP_
#define SERVERPINGMESSAGEHANDLER_HPP_

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/PingPacket.hpp"

#include "shared/Synchronizer/Synchronizer.hpp"

class ServerPingMessageHandler : public AMessageHandler<PingPacket> {
    public:
        ServerPingMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ServerPingMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, PingPacket &packet) {
            std::cout << "received" << std::endl;
            synchronizer.getDoubleMap().update();
            synchronizer.getDoubleQueue().update();
        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !SERVERPINGMESSAGEHANDLER_HPP_ */
