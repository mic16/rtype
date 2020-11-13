/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** MovePacket
*/

#ifndef CLIENTMOVEMESSAGEHANDLER_HPP_
#define CLIENTMOVEMESSAGEHANDLER_HPP_

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/MovePacket.hpp"

#include "shared/Synchronizer/Synchronizer.hpp"

class ClientMoveMessageHandler : public AMessageHandler<MovePacket> {
    public:
        ClientMoveMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ClientMoveMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, MovePacket &packet) {

        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !CLIENTMOVEMESSAGEHANDLER_HPP_ */
