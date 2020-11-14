/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** FirePacket
*/

#ifndef INSTANCIATEPLAYERPACKET_HPP
#define INSTANCIATEPLAYERPACKET_HPP

#include "ABasePacket.hpp"

class InstanciatePlayerPacket : public ABasePacket {
    public:
        InstanciatePlayerPacket(size_t id) : ABasePacket(id) {}

        InstanciatePlayerPacket() : ABasePacket() {}

        InstanciatePlayerPacket(InstanciatePlayerPacket &packet) : ABasePacket(packet) {}

        ~InstanciatePlayerPacket() {}

        void fromBuffer(ByteBuffer &buffer) override {
            ABasePacket::fromBuffer(buffer);
        }

        void toBuffer(ByteBuffer &buffer) override {
            ABasePacket::toBuffer(buffer);
        }

        size_t getPacketID() const override {
            return InstanciatePlayerPacket::PacketID();
        }

        static size_t PacketID() {
            return 6;
        }

    protected:
    private:
};

#endif /* !INSTANCIATEPLAYERPACKET_HPP */
