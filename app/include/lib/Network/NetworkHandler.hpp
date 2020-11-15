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

#include "shared/Packet/DeathPacket.hpp"

#include "AMessageHandler.hpp"
#include "INetworkClient.hpp"

#include "boost/iostreams/filter/zlib.hpp"
#include "lib/Compression/Compression.hpp"

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

        std::vector<std::unique_ptr<INetworkClient>> &getClients() {
            return clients;
        }

        void addClient(INetworkClient *client) {
            clients.emplace_back(client);
            lastClientRes.insert(std::pair<unsigned int, std::chrono::high_resolution_clock::time_point>(client->getId(), std::chrono::high_resolution_clock::now()));
        }

        void clear() {
            clients.clear();
            relatedEntityID.clear();
            lastClientRes.clear();
            playerStatus.clear();
        }

        template<typename T>
        void broadcast(T packet) {
            if (isClosed())
                return;

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

            broadcastBuffer.writeULong(id);
            broadcastBuffer.writeCharBuffer(reinterpret_cast<const char *>(buffer.flush()), buffer.getSize());
            flushBroadcast();
        }

        void flushBroadcast() {
            if (broadcastBuffer.getSize() > 0) {
                for (auto &client : clients) {
                    client->write(broadcastBuffer);
                }
                broadcastBuffer.clear();
            }
        }

        template<typename T>
        void send(INetworkClient &client, T packet) {

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
            client.write(prepend);
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

        std::chrono::high_resolution_clock::time_point &getLastTRequestStatus() {
            return (lastTRequestStatus);
        }

        std::chrono::high_resolution_clock::time_point &getLastClientRes(unsigned int clientid) {
            return lastClientRes[clientid];
        }

        void setPlayerEntityID(unsigned int playerID, unsigned int id) {
            relatedEntityID.insert(std::pair<unsigned int, unsigned int>(playerID, id));
            playerStatus.insert(std::pair<unsigned int, bool>(playerID, true));
        }

        bool isPlayer(unsigned int id) {
            for (auto it = relatedEntityID.begin(); it != relatedEntityID.end(); ++it) {
                if (it->second == id) {
                    return true;
                }
            }
            return false;
        }

        void stopPlay(unsigned int id) {
            for (auto it = relatedEntityID.begin(); it != relatedEntityID.end(); ++it) {
                if (it->second == id) {
                    playerStatus[it->first] = false;
                }
            }
        }

        bool havePlayerPlaying() {
            for (auto it = playerStatus.begin(); it != playerStatus.end(); ++it) {
                if (it->second) {
                    return true;
                }
            }
            return false;
        }

        void checkClientsConnection() {
            for (auto it = clients.begin(); it != clients.end();) {
                if (std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - lastClientRes[(*it)->getId()]).count() >= 25) {
                    broadcast(DeathPacket(relatedEntityID[(*it)->getId()]));
                    lastClientRes.erase((*it)->getId());
                    relatedEntityID.erase((*it)->getId());
                    it = clients.erase(it);
                } else {
                    ++it;
                }
            }
        }

        void close() {
            isClose = true;
        }

        void open() {
            isClose = false;
        }

        bool isClosed() {
            return isClose;
        }

    protected:
    private:
        bool isClose = false;
        ByteBuffer prepend = {1024};
        ByteBuffer broadcastBuffer = {1024};
        ByteBuffer buffer = {1024};
        std::vector<std::unique_ptr<INetworkClient>> clients;
        std::map<unsigned int, std::chrono::high_resolution_clock::time_point> lastClientRes;
        std::map<unsigned int, unsigned int> relatedEntityID;
        std::map<unsigned int, bool> playerStatus;
        std::chrono::high_resolution_clock::time_point lastTRequestStatus;
        std::size_t m_packetMaxSize;
        std::unordered_map<std::size_t, std::unique_ptr<IMessageHandler>> packetHandlers;
        std::unordered_map<std::size_t, std::size_t> packetsID;
};

#endif /* !NETWORKHANDLER_HPP_ */
