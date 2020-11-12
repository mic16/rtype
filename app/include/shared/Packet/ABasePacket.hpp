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

        void fromBuffer(ByteBuffer &buffer) {
            m_id = buffer.readUInt(nullptr);
        }

        void toBuffer(ByteBuffer &buffer) {
            buffer.writeUInt(m_id);
        }

        size_t getID() const {
            return m_id;
        }

    protected:
    private:
        size_t m_id;

};

#endif /* !BASEPACKET_HPP_ */
