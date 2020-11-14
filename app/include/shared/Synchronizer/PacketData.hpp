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
    bool isAlive = true;
    bool isFiring = false;
};

#endif /* !PACKETDATA_HPP_ */
