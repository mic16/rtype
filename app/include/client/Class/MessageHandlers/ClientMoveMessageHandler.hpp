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

class ClientMoveMessageHandler : public AMessageHandler<MovePacket> {
    public:
        ClientMoveMessageHandler() {}
        ~ClientMoveMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, MovePacket &packet) {

        }

    protected:
    private:
};

#endif /* !CLIENTMOVEMESSAGEHANDLER_HPP_ */
