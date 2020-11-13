/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** BasePacket
*/

#ifndef BASEPACKET_HPP_
#define BASEPACKET_HPP_

#include "lib/Network/IPacket.hpp"

class ABasePacket : public IPacket {
    public:
        ABasePacket(size_t id) : m_id(id) {}
        ABasePacket() {}
        ~ABasePacket() {}

        virtual void fromBuffer(ByteBuffer &buffer) override {
            m_id = buffer.readUInt(nullptr);
        }

        virtual void toBuffer(ByteBuffer &buffer) override {
            buffer.writeUInt(m_id);
        }

        size_t getEntityID() const {
            return m_id;
        }

        virtual size_t getPacketID() const = 0;

    protected:
    private:
        size_t m_id;

};

#endif /* !BASEPACKET_HPP_ */
