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
#include "PacketData.hpp"

#include <atomic>

class Synchronizer {
    public:
        Synchronizer() {}
        ~Synchronizer() {}

        DoubleHashmap<size_t, PacketData> &getDoubleMap() {
            return doubleMap;
        }

        DoubleQueue<std::unique_ptr<IPacket>> &getDoubleQueue() {
            return doubleQueue;
        }

        void update() {
            doubleQueue.update();
            doubleMap.update();
        }

        void finish() {
            end.store(true, std::memory_order::memory_order_relaxed);
        }

        bool isFinished() const {
            return end.load(std::memory_order::memory_order_relaxed);
        }

        void setPlayerId(size_t newId) {
            if (!isPlayerIdSet()) {
                m_isPlayerIdSet.store(true, std::memory_order::memory_order_relaxed);
                id.store(newId, std::memory_order::memory_order_relaxed);
            }
        }

        size_t getPlayerId() const {
            return id.load(std::memory_order::memory_order_relaxed);
        }

        bool isPlayerIdSet() const {
            return m_isPlayerIdSet.load(std::memory_order::memory_order_relaxed);
        }

    protected:
        std::atomic<bool> end = false;
        std::atomic<size_t> id = 0;
        std::atomic<bool> m_isPlayerIdSet = false;
        DoubleHashmap<size_t, PacketData> doubleMap;
        DoubleQueue<std::unique_ptr<IPacket>> doubleQueue;
    private:
};

#endif /* !SYNCHRONIZER_HPP_ */
