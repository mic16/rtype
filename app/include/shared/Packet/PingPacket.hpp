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
        PingPacket(size_t id) : ABasePacket(id), is_exists(false) {}
        PingPacket(size_t id, bool is_exists) : ABasePacket(id), is_exists(is_exists) {}
        PingPacket(ABasePacket &packet) : ABasePacket(packet) {}
        ~PingPacket() {}

        void fromBuffer(ByteBuffer &buffer) override {
            ABasePacket::fromBuffer(buffer);
            int err = 0;
            is_exists = buffer.readBool(&err);
            if (err) {
                setErrored();
            }
        }

        void toBuffer(ByteBuffer &buffer) override {
            ABasePacket::toBuffer(buffer);
            buffer.writeBool(is_exists);
        }

        size_t getPacketID() const override {
            return PingPacket::PacketID();
        }

        bool isExists() const {
            return is_exists;
        }

        static size_t PacketID() {
            return 200;
        }

    protected:
    private:
        bool is_exists;
};

#endif /* !PINGPACKET_HPP_ */
