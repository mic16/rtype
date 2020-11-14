/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** SpawnMessageHandler
*/

#ifndef CLIENTINSTANCIATEPLAYERMESSAGEHANDLER_HPP_
#define CLIENTINSTANCIATEPLAYERMESSAGEHANDLER_HPP_

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/InstanciatePlayerPacket.hpp"

#include "shared/Synchronizer/Synchronizer.hpp"

class ClientInstanciatePlayerMessageHandler : public AMessageHandler<InstanciatePlayerPacket> {
    public:
        ClientInstanciatePlayerMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ClientInstanciatePlayerMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, InstanciatePlayerPacket &packet) {
            auto &vector = synchronizer.getDoubleQueue().getWriteVector();
            vector->emplace_back(new InstanciatePlayerPacket(packet));
            synchronizer.update();
        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !CLIENTINSTANCIATEPLAYERMESSAGEHANDLER_HPP_ */
