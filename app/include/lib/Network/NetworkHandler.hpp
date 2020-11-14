/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** NetworkHandler
*/

#ifndef NETWORKHANDLER_HPP_
#define NETWORKHANDLER_HPP_

#include <unordered_map>
#include <memory>
#include <iostream>
#include <exception>

#include "AMessageHandler.hpp"
#include "INetworkClient.hpp"

class NetworkHandler {
    public:
        NetworkHandler(std::size_t packetMaxSize) : m_packetMaxSize(packetMaxSize) {

        }

        ~NetworkHandler() {

        }

        template<typename T>
        void registerMessageHandler(T type) {
            static_assert(std::is_base_of<IMessageHandler, typename std::remove_pointer<T>::type>::value, "Class not derived from AMessageHandler");
            static_assert(std::is_pointer<T>::value, "Expected a pointer, not a copy or reference");
            std::size_t hashcode = typeid(typename std::remove_pointer<T>::type::packetType).hash_code();

            typename std::remove_pointer<T>::type::packetType packet;
            size_t id = packet.getPacketID();

            packetHandlers.insert(std::make_pair(id, std::unique_ptr<IMessageHandler>(reinterpret_cast<IMessageHandler *>(type))));
            packetsID.insert({hashcode, id});
        }

        void addClient(INetworkClient *client) {
            clients.emplace_back(client);
            buffers.emplace_back(new ByteBuffer(1024));
            clientStatus.emplace_back(std::make_pair(true, true));
        }

        void clear() {
            clients.clear();
            buffers.clear();
            clientStatus.clear();
        }

        template<typename T>
        void broadcast(T packet) {

            static_assert(std::is_pointer<T>::value || std::is_reference<T>::value || std::is_object<T>::value, "Cannot broadcast an unsupported type");

            buffer.clear();

            std::size_t hashcode;
            if constexpr(std::is_pointer<T>::value) {
                static_assert(std::is_base_of<IPacket, typename std::remove_pointer<T>::type>::value, "Cannot broadcast something that is not a child of IPacket");
                packet->toBuffer(buffer);
                hashcode = typeid(typename std::remove_pointer<T>::type).hash_code();
            } else if constexpr(std::is_reference<T>::value) {
                static_assert(std::is_base_of<IPacket, typename std::remove_reference<T>::type>::value, "Cannot broadcast something that is not a child of IPacket");
                packet.toBuffer(buffer);
                hashcode = typeid(typename std::remove_reference<T>::type).hash_code();
            } else if constexpr(std::is_object<T>::value) {
                static_assert(std::is_base_of<IPacket, T>::value, "Cannot broadcast something that is not a child of IPacket");
                packet.toBuffer(buffer);
                hashcode = typeid(T).hash_code();
            }

            if (packetsID.find(hashcode) == packetsID.end()) {
                return;
            }

            std::size_t id = packetsID[hashcode];

            prepend.clear();
            prepend.writeULong(id);
            prepend.writeCharBuffer(reinterpret_cast<const char *>(buffer.flush()), buffer.getSize());
            for (size_t i = 0; i < clients.size() && i < clientStatus.size(); i++) {
                if (clientStatus[i].second) {
                    clients[i]->write(prepend);
                }
            }
        }

        void askStatus() {
            for (std::pair<bool, bool> &status : clientStatus) {
                status.first = false;
            }
        }

        void processMessage(INetworkClient &client) {
            ByteBuffer &buffer = client.getBuffer();
            int err = 0;
            while (buffer.getSize() > 0) {
                size_t packedType = buffer.readULong(&err);
                if (err) {
                    buffer.clear();
                    return;
                }

                size_t buffSize = buffer.readUInt(&err);
                if (err) {
                    buffer.clear();
                    return;
                }

                if (packetHandlers.find(packedType) == packetHandlers.end()) {
                    buffer.move(buffSize);
                    return;
                }

                auto &messageHandler = packetHandlers[packedType];

                messageHandler->processMessage(*this, client, buffer);
            }

        }

    protected:
    private:

        ByteBuffer prepend = {1024};
        ByteBuffer buffer = {1024};
        std::vector<std::unique_ptr<INetworkClient>> clients;
        std::vector<std::unique_ptr<ByteBuffer>> buffers;
        std::vector<std::pair<bool, bool>> clientStatus;
        std::size_t m_packetMaxSize;
        std::unordered_map<std::size_t, std::unique_ptr<IMessageHandler>> packetHandlers;
        std::unordered_map<std::size_t, std::size_t> packetsID;
};

#endif /* !NETWORKHANDLER_HPP_ */
