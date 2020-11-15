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
        PositionPacket(size_t id, double x, double y, size_t entityType) : ABasePacket(id), x(x), y(y), entityType(entityType) {}

        PositionPacket() : ABasePacket() {}

        PositionPacket(PositionPacket &packet) : ABasePacket(packet), x(packet.x), y(packet.y), entityType(packet.entityType) {}

        ~PositionPacket() {}

        void fromBuffer(ByteBuffer &buffer) override {
            ABasePacket::fromBuffer(buffer);
            int err = 0;
            x = buffer.readDouble(&err);
            if (err) setErrored();
            y = buffer.readDouble(&err);
            if (err) setErrored();
            entityType = buffer.readUInt(&err);
            if (err) setErrored();
        }

        void toBuffer(ByteBuffer &buffer) override {
            ABasePacket::toBuffer(buffer);
            buffer.writeDouble(x);
            buffer.writeDouble(y);
            buffer.writeUInt(entityType);
        }

        size_t getEntityType() const {
            return entityType;
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
        size_t entityType = 0;
        double x;
        double y;
};

#endif /* !POSITIONPACKET_HPP_ */
