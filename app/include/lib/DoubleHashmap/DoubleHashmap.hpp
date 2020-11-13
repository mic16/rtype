/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** DoubleHashmap
*/

#ifndef DOUBLEHASHMAP_HPP_
#define DOUBLEHASHMAP_HPP_

#include <memory>
#include <unordered_map>
#include <atomic>

template<typename T, typename U>
class DoubleHashmap {
    public:
        DoubleHashmap() {
            writeMap = std::make_unique<std::unordered_map<T, U>>();
            readMap = std::make_unique<std::unordered_map<T, U>>();
        }
        ~DoubleHashmap() {}

        void update() {
            if (isReadingFinished()) {
                readMap->clear();
                writeMap.swap(readMap);
                readEnd.store(false, std::memory_order::memory_order_relaxed);
            }
        }

        std::unique_ptr<std::unordered_map<T, U>> &getWriteMap() const {
            return &writeMap;
        }

        const std::unique_ptr<std::unordered_map<T, U>> &getReadMap() const {
            return &readMap;
        }

        void finishReading() {
            readEnd.store(true, std::memory_order::memory_order_relaxed);
        }

        bool isReadingFinished() {
            return readEnd.load(std::memory_order::memory_order_relaxed);
        }

    protected:
    private:
        std::atomic<bool> readEnd = false;
        std::unique_ptr<std::unordered_map<T, U>> writeMap;
        std::unique_ptr<std::unordered_map<T, U>> readMap;
};

#endif /* !DOUBLEHASHMAP_HPP_ */
