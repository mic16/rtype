/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** DeathPacket
*/

#ifndef DEATHPACKET_HPP_
#define DEATHPACKET_HPP_

#include "ABasePacket.hpp"

class DeathPacket : public ABasePacket {
    public:
        DeathPacket() : ABasePacket() {}
        DeathPacket(size_t id) : ABasePacket(id) {}
        ~DeathPacket() {}

        void fromBuffer(ByteBuffer &buffer) {
            ABasePacket::fromBuffer(buffer);
        }

        void toBuffer(ByteBuffer &buffer) {
            ABasePacket::toBuffer(buffer);
        }

    protected:
    private:
};

#endif /* !DEATHPACKET_HPP_ */
