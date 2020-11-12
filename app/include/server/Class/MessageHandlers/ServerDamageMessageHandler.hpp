/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** DamagePacket
*/

#ifndef SERVERDAMAGEMESSAGEHANDLER_HPP
#define SERVERDAMAGEMESSAGEHANDLER_HPP

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/DamagePacket.hpp"

class ServerDamageMessageHandler : public AMessageHandler<DamagePacket> {
    public:
        ServerDamageMessageHandler() {}
        ~ServerDamageMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, DamagePacket &packet) {

        }

    protected:
    private:
};

#endif /* !SERVERDAMAGEMESSAGEHANDLER_HPP */
