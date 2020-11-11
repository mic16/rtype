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

        ~FirePacket() {}

        void fromBuffer(ByteBuffer &buffer) {
            ABasePacket::fromBuffer(buffer);
            holding = buffer.readBool(nullptr);
        }

        void toBuffer(ByteBuffer &buffer) {
            ABasePacket::toBuffer(buffer);
            buffer.writeBool(holding);
        }

        double isHolding() const {
            return holding;
        }

    protected:
    private:
        bool holding = false;
};

#endif /* !FIREPACKET_HPP_ */
