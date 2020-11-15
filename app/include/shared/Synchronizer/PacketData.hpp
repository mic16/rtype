/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** PacketData
*/

#ifndef PACKETDATA_HPP_
#define PACKETDATA_HPP_

struct PacketData {
    PacketData() {}
    ~PacketData() {}
    double x, y;
    int dirX, dirY;
    size_t entityType;
    size_t lastPosUpdate = 0;
    bool isAlive = true;
    bool isFiring = false;
    bool fireChanged = false;
    bool moveChanged = false;
};

#endif /* !PACKETDATA_HPP_ */
