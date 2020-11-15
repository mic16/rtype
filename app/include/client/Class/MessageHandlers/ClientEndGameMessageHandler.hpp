/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** ClientEndGameMessageHandler
*/

#ifndef CLIENTENDGAMEMESSAGEHANDLER_HPP_
#define CLIENTENDGAMEMESSAGEHANDLER_HPP_

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/EndGamePacket.hpp"

#include "shared/Synchronizer/Synchronizer.hpp"

class ClientEndGameMessageHandler : public AMessageHandler<EndGamePacket> {
    public:
        ClientEndGameMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ClientEndGameMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, EndGamePacket &packet) {
            synchronizer.finish();
            synchronizer.update();
        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !CLIENTENDGAMEMESSAGEHANDLER_HPP_ */
