/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** ServerEndGameMessageHandler
*/

#ifndef SERVERENDGAMEMESSAGEHANDLER_HPP_
#define SERVERENDGAMEMESSAGEHANDLER_HPP_

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/EndGamePacket.hpp"

#include "shared/Synchronizer/Synchronizer.hpp"

class ServerEndGameMessageHandler : public AMessageHandler<EndGamePacket> {
    public:
        ServerEndGameMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ServerEndGameMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, EndGamePacket &packet) {

        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !SERVERENDGAMEMESSAGEHANDLER_HPP_ */
