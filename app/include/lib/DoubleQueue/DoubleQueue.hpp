/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** DoubleQueue
*/

#ifndef DOUBLEQUEUE_HPP_
#define DOUBLEQUEUE_HPP_

#include <vector>
#include <atomic>

template<typename T>
class DoubleQueue {
    public:
        DoubleQueue() {
            writeVector = std::make_unique<std::vector<T>>();
            readVector = std::make_unique<std::vector<T>>();
        }
        ~DoubleQueue() {}

        void update() {
            if (isReadingFinished()) {
                readVector->clear();
                writeVector.swap(readVector);
                readEnd.load(false, std::memory_order::memory_order_relaxed);
            }
        }

        std::unique_ptr<std::vector<T>> &getWriteVector() const {
            return &writeVector;
        }

        const std::unique_ptr<std::vector<T>> &getReadVector() const {
            return &readVector;
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
        std::unique_ptr<std::vector<T>> writeVector;
        std::unique_ptr<std::vector<T>> readVector;
};

#endif /* !DOUBLEQUEUE_HPP_ */
