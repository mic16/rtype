/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** DamagePacket
*/

#ifndef DAMAGEPACKET_HPP_
#define DAMAGEPACKET_HPP_

#include "ABasePacket.hpp"

class DamagePacket : public ABasePacket {
    public:
        DamagePacket() : ABasePacket() {}
        DamagePacket(size_t id, int damage, int hp, int maxHP) : ABasePacket(id), damage(damage), hp(hp), maxHP(maxHP) {}
        DamagePacket(DamagePacket &packet) : ABasePacket(packet), damage(packet.damage), hp(packet.hp), maxHP(packet.maxHP) {}
        ~DamagePacket() {}

        virtual void fromBuffer(ByteBuffer &buffer) override {
            ABasePacket::fromBuffer(buffer);
            damage = buffer.readInt(nullptr);
            hp = buffer.readInt(nullptr);
            maxHP = buffer.readInt(nullptr);
        }

        virtual void toBuffer(ByteBuffer &buffer) override {
            ABasePacket::toBuffer(buffer);
            buffer.writeInt(damage);
            buffer.writeInt(hp);
            buffer.writeInt(maxHP);
        }

        int getDamage() const {
            return damage;
        }

        int getHP() const {
            return hp;
        }

        int getMaxHP() const {
            return maxHP;
        }

        size_t getPacketID() const override {
            return DamagePacket::PacketID();
        }

        static size_t PacketID() {
            return 0;
        }

    protected:
    private:
        int damage;
        int hp;
        int maxHP;
};

#endif /* !DAMAGEPACKET_HPP_ */
