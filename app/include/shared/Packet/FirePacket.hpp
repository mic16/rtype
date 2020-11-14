/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** FirePacket
*/

#ifndef FIREPACKET_HPP_
#define FIREPACKET_HPP_

#include "ABasePacket.hpp"

class FirePacket : public ABasePacket {
    public:
        FirePacket(size_t id, bool holding) : ABasePacket(id), holding(holding) {}

        FirePacket() : ABasePacket() {}

        FirePacket(FirePacket &packet) : ABasePacket(packet), holding(packet.holding) {}

        ~FirePacket() {}

        void fromBuffer(ByteBuffer &buffer) override {
            ABasePacket::fromBuffer(buffer);
            holding = buffer.readBool(nullptr);
        }

        void toBuffer(ByteBuffer &buffer) override {
            ABasePacket::toBuffer(buffer);
            buffer.writeBool(holding);
        }

        bool isHolding() const {
            return holding;
        }

        size_t getPacketID() const override {
            return FirePacket::PacketID();
        }

        static size_t PacketID() {
            return 2;
        }

    protected:
    private:
        bool holding = false;
};

#endif /* !FIREPACKET_HPP_ */
