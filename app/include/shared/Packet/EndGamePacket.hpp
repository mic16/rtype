/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** EndGamePacket
*/

#ifndef ENDGAMEPACKET_HPP_
#define ENDGAMEPACKET_HPP_

#include "ABasePacket.hpp"

class EndGamePacket : public ABasePacket {
    public:
        EndGamePacket() : ABasePacket() {}
        EndGamePacket(size_t id) : ABasePacket(id) {}
        EndGamePacket(ABasePacket &packet) : ABasePacket(packet) {}
        ~EndGamePacket() {}

        void fromBuffer(ByteBuffer &buffer) override {
            ABasePacket::fromBuffer(buffer);
        }

        void toBuffer(ByteBuffer &buffer) override {
            ABasePacket::toBuffer(buffer);
        }

        size_t getPacketID() const override {
            return EndGamePacket::PacketID();
        }

        static size_t PacketID() {
            return 300;
        }

    protected:
    private:
};

#endif /* !ENDGAMEPACKET_HPP_ */
