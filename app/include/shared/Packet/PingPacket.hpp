/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** PingPacket
*/

#ifndef PINGPACKET_HPP_
#define PINGPACKET_HPP_

#include "ABasePacket.hpp"

class PingPacket : public ABasePacket {
    public:
        PingPacket() : ABasePacket() {}
        PingPacket(size_t id) : ABasePacket(id) {}
        PingPacket(ABasePacket &packet) : ABasePacket(packet) {}
        ~PingPacket() {}

        void fromBuffer(ByteBuffer &buffer) override {
            ABasePacket::fromBuffer(buffer);
        }

        void toBuffer(ByteBuffer &buffer) override {
            ABasePacket::toBuffer(buffer);
        }

        size_t getPacketID() const override {
            return PingPacket::PacketID();
        }

        static size_t PacketID() {
            return 200;
        }

    protected:
    private:
};

#endif /* !PINGPACKET_HPP_ */
