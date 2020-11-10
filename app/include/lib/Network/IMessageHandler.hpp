/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** IMessageHandler
*/

#ifndef IMESSAGEHANDLER_HPP_
#define IMESSAGEHANDLER_HPP_

#include "lib/ByteBuffer/ByteBuffer.hpp"
#include "INetworkClient.hpp"

class NetworkHandler;

class IMessageHandler {
    public:
        virtual void processMessage(NetworkHandler &handler, INetworkClient &client, ByteBuffer &buffer) = 0;

    protected:
    private:
};

#endif /* !IMESSAGEHANDLER_HPP_ */
