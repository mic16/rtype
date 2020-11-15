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
        DeathPacket(ABasePacket &packet) : ABasePacket(packet) {}
        ~DeathPacket() {}

        void fromBuffer(ByteBuffer &buffer) override {
            ABasePacket::fromBuffer(buffer);
        }

        void toBuffer(ByteBuffer &buffer) override {
            ABasePacket::toBuffer(buffer);
        }

        size_t getPacketID() const override {
            return DeathPacket::PacketID();
        }

        static size_t PacketID() {
            return 1;
        }

        bool Acknowledge() { return true; }

    protected:
    private:
};

#endif /* !DEATHPACKET_HPP_ */
