/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** TestPacket
*/

#ifndef TESTPACKET_HPP_
#define TESTPACKET_HPP_

#include "lib/Network/IPacket.hpp"
#include <string>

class TestPacket : public IPacket {
    public:
        TestPacket() {};
        TestPacket(const std::string &message): message(message) {};
        ~TestPacket() {};

        void fromBuffer(ByteBuffer &buffer) {
            int err = 0;
            std::string *newMessage = buffer.readString(&err);

            if (!err) {
                message = *newMessage;
                delete newMessage;
            }
        };

        void toBuffer(ByteBuffer &buffer) {
            buffer.writeString(message);
        };

        const std::string &getMessage() {
            return message;
        }

        private:
            std::string message;
};

#endif /* !TESTPACKET_HPP_ */
