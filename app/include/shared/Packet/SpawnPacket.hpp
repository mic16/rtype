/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** SpawnPacket
*/

#ifndef SPAWNPACKET_HPP_
#define SPAWNPACKET_HPP_

#include "PositionPacket.hpp"

class SpawnPacket : public PositionPacket {
    public:
        SpawnPacket() : PositionPacket() {}
        SpawnPacket(size_t id, size_t entityType, double x, double y) : PositionPacket(id, x, y), entityType(entityType) {}
        ~SpawnPacket() {}

        void fromBuffer(ByteBuffer &buffer) override {
            PositionPacket::fromBuffer(buffer);
            entityType = buffer.readUInt(nullptr);
        }

        void toBuffer(ByteBuffer &buffer) override {
            PositionPacket::toBuffer(buffer);
            buffer.writeUInt(entityType);
        }

        size_t getEntityType() const {
            return entityType;
        }

        size_t getPacketID() const override {
            return SpawnPacket::PacketID();
        }

        static size_t PacketID() {
            return 5;
        }

    protected:
    private:
        size_t entityType = 0;
};

#endif /* !SPAWNPACKET_HPP_ */

