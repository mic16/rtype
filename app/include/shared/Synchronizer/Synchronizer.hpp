/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Synchronizer
*/

#ifndef SYNCHRONIZER_HPP_
#define SYNCHRONIZER_HPP_

#include <memory>

#include "lib/DoubleHashmap/DoubleHashmap.hpp"
#include "lib/DoubleQueue/DoubleQueue.hpp"
#include "lib/Network/IPacket.hpp"

class Synchronizer {
    public:
        Synchronizer() {}
        ~Synchronizer() {}

        DoubleHashmap<size_t, std::unique_ptr<IPacket>> &getDoubleMap() {
            return doubleMap;
        }

        DoubleQueue<std::unique_ptr<IPacket>> &getDoubleQueue() {
            return doubleQueue;
        }

    protected:
        DoubleHashmap<size_t, std::unique_ptr<IPacket>> doubleMap;
        DoubleQueue<std::unique_ptr<IPacket>> doubleQueue;
    private:
};

#endif /* !SYNCHRONIZER_HPP_ */
