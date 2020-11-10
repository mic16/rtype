/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** AMessageHandler
*/

#ifndef AMESSAGEHANDLER_HPP_
#define AMESSAGEHANDLER_HPP_

#include "IMessageHandler.hpp"
#include "IPacket.hpp"

template<typename T>
class AMessageHandler : IMessageHandler {
    public:
        typedef T packetType;
        AMessageHandler() {
            static_assert(std::is_base_of<IPacket, T>::value, "Class not derived from IPacket");
        }
        ~AMessageHandler() {

        }

        virtual void onMessage(T &) = 0;

        void processMessage(ByteBuffer &buffer) {
            T packet;
            packet.fromBuffer(buffer);
            onMessage(packet);
        }

    protected:
    private:

};

#endif /* !AMESSAGEHANDLER_HPP_ */
