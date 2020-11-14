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

        PositionPacket(PositionPacket &packet) : ABasePacket(packet), x(packet.x), y(packet.y) {}

        ~PositionPacket() {}

        void fromBuffer(ByteBuffer &buffer) override {
            ABasePacket::fromBuffer(buffer);
            x = buffer.readDouble(nullptr);
            y = buffer.readDouble(nullptr);
        }

        void toBuffer(ByteBuffer &buffer) override {
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

        size_t getPacketID() const override {
            return PositionPacket::PacketID();
        }

        static size_t PacketID() {
            return 4;
        }

    protected:
    private:
        double x;
        double y;
};

#endif /* !POSITIONPACKET_HPP_ */
