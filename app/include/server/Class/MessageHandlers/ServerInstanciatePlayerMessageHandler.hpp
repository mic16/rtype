/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** SpawnMessageHandler
*/

#ifndef SERVERINSTANCIATEPLAYERMESSAGEHANDLER_HPP_
#define SERVERINSTANCIATEPLAYERMESSAGEHANDLER_HPP_

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/InstanciatePlayerPacket.hpp"

#include "shared/Synchronizer/Synchronizer.hpp"

class ServerInstanciatePlayerMessageHandler : public AMessageHandler<InstanciatePlayerPacket> {
    public:
        ServerInstanciatePlayerMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ServerInstanciatePlayerMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, InstanciatePlayerPacket &packet) {

        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !SERVERINSTANCIATEPLAYERMESSAGEHANDLER_HPP_ */
