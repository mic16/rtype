/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** ServerPingMessageHandler
*/

#ifndef SERVERPINGMESSAGEHANDLER_HPP_
#define SERVERPINGMESSAGEHANDLER_HPP_

#include <chrono>
#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/PingPacket.hpp"

#include "shared/Synchronizer/Synchronizer.hpp"

class ServerPingMessageHandler : public AMessageHandler<PingPacket> {
    public:
        ServerPingMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ServerPingMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, PingPacket &packet) {
            if (handler.getClientConnection(client.getId())) {
                handler.getLastClientRes(client.getId()) = std::chrono::high_resolution_clock::now();
            }
            synchronizer.update();
        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !SERVERPINGMESSAGEHANDLER_HPP_ */
