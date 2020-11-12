/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** PositionPacket
*/

#ifndef POSITIONPACKET_HPP_
#define POSITIONPACKET_HPP_

#include "ABasePacket.hpp"

class PositionPacket : public ABasePacket {
    public:
        PositionPacket(size_t id, double x, double y) : ABasePacket(id), x(x), y(y) {}

        PositionPacket() : ABasePacket() {}

        ~PositionPacket() {}

        void fromBuffer(ByteBuffer &buffer) {
            ABasePacket::fromBuffer(buffer);
            x = buffer.readDouble(nullptr);
            y = buffer.readDouble(nullptr);
        }

        void toBuffer(ByteBuffer &buffer) {
            ABasePacket::toBuffer(buffer);
            buffer.writeDouble(x);
            buffer.writeDouble(y);
        }

        double getX() const {
            return x;
        }

        double getY() const {
            return y;
        }

    protected:
    private:
        double x;
        double y;
};

#endif /* !POSITIONPACKET_HPP_ */
