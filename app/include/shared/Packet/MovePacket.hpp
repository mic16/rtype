/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** MovePacket
*/

#ifndef MOVEPACKET_HPP_
#define MOVEPACKET_HPP_

#include "ABasePacket.hpp"

class MovePacket : public ABasePacket {
    public:
        MovePacket(size_t id, int dirX, int dirY) : ABasePacket(id), dirX(dirX), dirY(dirY) {}

        MovePacket() : ABasePacket() {}

        MovePacket(MovePacket &packet) : ABasePacket(packet), dirX(packet.dirX), dirY(packet.dirY) {}

        ~MovePacket() {}

        void fromBuffer(ByteBuffer &buffer) override {
            ABasePacket::fromBuffer(buffer);
            dirX = buffer.readInt(nullptr);
            dirY = buffer.readInt(nullptr);
        }

        void toBuffer(ByteBuffer &buffer) override {
            ABasePacket::toBuffer(buffer);
            buffer.writeInt(dirX);
            buffer.writeInt(dirY);
        }

        int getDirectionX() const {
            return dirX;
        }

        int getDirectionY() const {
            return dirY;
        }

        size_t getPacketID() const override {
            return MovePacket::PacketID();
        }

        static size_t PacketID() {
            return 3;
        }

    protected:
    private:
        int dirX;
        int dirY;
};

#endif /* !MOVEPACKET_HPP_ */
