/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** DamagePacket
*/

#ifndef CLIENTDAMAGEMESSAGEHANDLER_HPP
#define CLIENTDAMAGEMESSAGEHANDLER_HPP

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/DamagePacket.hpp"

#include "shared/Synchronizer/Synchronizer.hpp"

class ClientDamageMessageHandler : public AMessageHandler<DamagePacket> {
    public:
        ClientDamageMessageHandler(Synchronizer &synchronizer) : synchronizer(synchronizer) {}
        ~ClientDamageMessageHandler() {}

        void onMessage(NetworkHandler &handler, INetworkClient &client, DamagePacket &packet) {

        }

    protected:
    private:
        Synchronizer &synchronizer;
};

#endif /* !CLIENTDAMAGEMESSAGEHANDLER_HPP */
