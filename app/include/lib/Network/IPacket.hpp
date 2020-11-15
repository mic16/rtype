/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** IPacket
*/

#ifndef IPACKET_HPP_
#define IPACKET_HPP_

#include "lib/ByteBuffer/ByteBuffer.hpp"

class IPacket {
    public:
        virtual void fromBuffer(ByteBuffer &buffer) = 0;
        virtual void toBuffer(ByteBuffer &buffer) = 0;
        virtual size_t getPacketID() const = 0;
        virtual void setErrored() = 0;
        virtual bool isErrored() = 0;

    protected:
    private:
};

#endif /* !IPACKET_HPP_ */
