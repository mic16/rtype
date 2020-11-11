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
        ~DamagePacket() {}

        void fromBuffer(ByteBuffer &buffer) {
            ABasePacket::fromBuffer(buffer);
            damage = buffer.readInt(nullptr);
            hp = buffer.readInt(nullptr);
            maxHP = buffer.readInt(nullptr);
        }

        void toBuffer(ByteBuffer &buffer) {
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

    protected:
    private:
        int damage;
        int hp;
        int maxHP;
};

#endif /* !DAMAGEPACKET_HPP_ */
