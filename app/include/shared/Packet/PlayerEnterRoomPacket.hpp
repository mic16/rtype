/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** FirePacket
*/

#ifndef PLAYERENTERROOMPACKET_HPP_
#define PLAYERENTERROOMPACKET_HPP_

#include "ABasePacket.hpp"
#include "lib/Network/INetworkClient.hpp"

class PlayerEnterRoomPacket : public IPacket {
    public:
        PlayerEnterRoomPacket(INetworkClient *client) : client(client) {}

        PlayerEnterRoomPacket() {}

        PlayerEnterRoomPacket(PlayerEnterRoomPacket &packet) : client(packet.client) {}

        ~PlayerEnterRoomPacket() {}

        void fromBuffer(ByteBuffer &buffer) override {

        }

        void toBuffer(ByteBuffer &buffer) override {

        }

        size_t getPacketID() const override {
            return PlayerEnterRoomPacket::PacketID();
        }

        static size_t PacketID() {
            return 8;
        }

        INetworkClient *getNetworkClient() {
            return client;
        }

        size_t getEntityID() { return 0; }

        void setErrored() {}
        bool isErrored() {return false; }

        bool Acknowledge() { return false; }

    protected:
    private:
        INetworkClient *client;
};

#endif /* !PLAYERENTERROOMPACKET_HPP_ */
