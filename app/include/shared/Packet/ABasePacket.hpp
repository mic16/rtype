/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** BasePacket
*/

#ifndef BASEPACKET_HPP_
#define BASEPACKET_HPP_

#include "lib/Network/IPacket.hpp"
#include <chrono>

class ABasePacket : public IPacket {
    public:
        ABasePacket(size_t id) : m_id(id) {
            auto now = std::chrono::system_clock::now();
            m_time = now.time_since_epoch().count();
        }
        ABasePacket() {
            auto now = std::chrono::system_clock::now();
            m_time = now.time_since_epoch().count();
        }
        ABasePacket(ABasePacket &packet) : m_time(packet.m_time), m_id(packet.m_id) {}
        ~ABasePacket() {}

        virtual void fromBuffer(ByteBuffer &buffer) override {
            int err = 0;
            m_time = buffer.readULong(&err);
            if (err) setErrored();
            m_id = buffer.readULong(&err);
            if (err) setErrored();
        }

        virtual void toBuffer(ByteBuffer &buffer) override {
            buffer.writeULong(m_time);
            buffer.writeULong(m_id);
        }

        size_t getEntityID() const {
            return m_id;
        }

        size_t getTime() {
            return m_time;
        }

        virtual size_t getPacketID() const = 0;

        bool isErrored() {
            return errored;
        }

        void setErrored() {
            errored = true;
        }

    protected:
    private:
        size_t m_id;
        size_t m_time;
        bool errored = false;

};

#endif /* !BASEPACKET_HPP_ */
