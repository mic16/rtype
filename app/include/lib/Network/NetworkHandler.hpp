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
#include "shared/Packet/SpawnPacket.hpp"

#include "AMessageHandler.hpp"
#include "INetworkClient.hpp"

#include "boost/iostreams/filter/zlib.hpp"
#include "lib/Compression/Compression.hpp"

class PacketBuff {
public:
    PacketBuff(size_t count) : count(count), buffer(128) {}
    PacketBuff(PacketBuff &&old) : count(old.count), buffer(std::move(old.buffer)) {}
    ~PacketBuff() {}
    size_t count = 0;
    ByteBuffer buffer;
};

class PacketInfo {
public:
    PacketInfo(size_t id) : id(id), timestamp(0), client(nullptr) {}
    ~PacketInfo() {}
    size_t id;
    long timestamp;
    INetworkClient *client;
};

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
        }

        template<typename T>
        void broadcast(T packet) {
            if (isClosed())
                return;

            static_assert(std::is_pointer<T>::value || std::is_reference<T>::value || std::is_object<T>::value, "Cannot broadcast an unsupported type");

            buffer.clear();

            size_t hashcode;
            size_t entityID;
            bool acknowledge = false;
            if constexpr(std::is_pointer<T>::value) {
                static_assert(std::is_base_of<IPacket, typename std::remove_pointer<T>::type>::value, "Cannot broadcast something that is not a child of IPacket");
                packet->toBuffer(buffer);
                hashcode = typeid(typename std::remove_pointer<T>::type).hash_code();
                entityID = packet->getEntityID();
                acknowledge = packet->Acknowledge();
            } else if constexpr(std::is_reference<T>::value) {
                static_assert(std::is_base_of<IPacket, typename std::remove_reference<T>::type>::value, "Cannot broadcast something that is not a child of IPacket");
                packet.toBuffer(buffer);
                hashcode = typeid(typename std::remove_reference<T>::type).hash_code();
                entityID = packet.getEntityID();
                acknowledge = packet.Acknowledge();
            } else if constexpr(std::is_object<T>::value) {
                static_assert(std::is_base_of<IPacket, T>::value, "Cannot broadcast something that is not a child of IPacket");
                packet.toBuffer(buffer);
                hashcode = typeid(T).hash_code();
                entityID = packet.getEntityID();
                acknowledge = packet.Acknowledge();
            }

            if (packetsID.find(hashcode) == packetsID.end()) {
                return;
            }

            std::size_t id = packetsID[hashcode];

            if (id == SpawnPacket::PacketID()) {
                std::cout << "Ack Spawn: " << acknowledge << std::endl;
            }

            if (id == DeathPacket::PacketID()) {
                auto it = packetsID.begin();
                while (it != packetsID.end()) {
                    size_t id = it->second;
                    size_t fingerprint = ((id & 0xFF) << 48) | (entityID & 0xFFFFFFFFFFFF);
                    for (auto &client : clients) {
                        size_t subfingerprint = ((static_cast<size_t>(client->getId()) & 0xFF) << 56) | fingerprint;
                        packetstatus.erase(subfingerprint);
                    }
                    packetsbuffer.erase(fingerprint);
                    it++;
                }
            }

            if (acknowledge) {
                size_t fingerprint = ((id & 0xFF) << 48) | (entityID & 0xFFFFFFFFFFFF);

                auto it = packetsbuffer.find(fingerprint);
                if (it == packetsbuffer.end()) {
                    it = packetsbuffer.emplace(std::make_pair(fingerprint, PacketBuff(clients.size()))).first;
                }

                PacketBuff &pbuff = it->second;

                pbuff.buffer.clear();
                pbuff.buffer.writeBool(true);
                pbuff.buffer.writeULong(id+1);
                pbuff.buffer.writeULong(fingerprint);
                pbuff.buffer.writeCharBuffer(reinterpret_cast<const char *>(buffer.flush()), buffer.getSize());
                for (auto &client : clients) {
                    size_t subfingerprint = ((static_cast<size_t>(client->getId()) & 0xFF) << 56) | fingerprint;
                    client->write(pbuff.buffer);
                    auto itpstatus = packetstatus.find(subfingerprint);
                    if (itpstatus == packetstatus.end()) {
                        itpstatus = packetstatus.emplace(std::make_pair(subfingerprint, PacketInfo(fingerprint))).first;
                        itpstatus->second.client = client.get();
                    }
                    PacketInfo &info = itpstatus->second;
                    info.timestamp = 0;
                }
            } else {
                broadcastBuffer.clear();
                broadcastBuffer.writeBool(false);
                broadcastBuffer.writeULong(id+1);
                broadcastBuffer.writeULong(0);
                broadcastBuffer.writeCharBuffer(reinterpret_cast<const char *>(buffer.flush()), buffer.getSize());
                for (auto &client : clients) {
                    client->write(broadcastBuffer);
                }
            }
        }

        void flushBroadcast() {
            auto it = packetstatus.begin();
            long now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            while (it != packetstatus.end()) {
                if (it->second.timestamp == 0) {
                    it->second.timestamp = now;
                } else {
                    long elapsed = now - it->second.timestamp;
                    if (elapsed > 100'000'000L) {
                        std::cout << "Timeout: [" << elapsed << "] " << (it->second.id >> 6) << std::endl;
                        auto buff = packetsbuffer.find(it->second.id);
                        if (buff != packetsbuffer.end()) {
                            it->second.client->write(buff->second.buffer);
                            it->second.timestamp = now;
                        } else {
                            it = packetstatus.erase(it);
                            continue;
                        }
                    }
                }
                it++;
            }
        }

        template<typename T>
        void send(INetworkClient &client, T packet) {

            static_assert(std::is_pointer<T>::value || std::is_reference<T>::value || std::is_object<T>::value, "Cannot broadcast an unsupported type");

            buffer.clear();

            size_t hashcode;
            size_t entityID;
            bool acknowledge = false;
            if constexpr(std::is_pointer<T>::value) {
                static_assert(std::is_base_of<IPacket, typename std::remove_pointer<T>::type>::value, "Cannot broadcast something that is not a child of IPacket");
                packet->toBuffer(buffer);
                hashcode = typeid(typename std::remove_pointer<T>::type).hash_code();
                entityID = packet->getEntityID();
                acknowledge = packet->Acknowledge();
            } else if constexpr(std::is_reference<T>::value) {
                static_assert(std::is_base_of<IPacket, typename std::remove_reference<T>::type>::value, "Cannot broadcast something that is not a child of IPacket");
                packet.toBuffer(buffer);
                hashcode = typeid(typename std::remove_reference<T>::type).hash_code();
                entityID = packet.getEntityID();
                acknowledge = packet.Acknowledge();
            } else if constexpr(std::is_object<T>::value) {
                static_assert(std::is_base_of<IPacket, T>::value, "Cannot broadcast something that is not a child of IPacket");
                packet.toBuffer(buffer);
                hashcode = typeid(T).hash_code();
                entityID = packet.getEntityID();
                acknowledge = packet.Acknowledge();
            }

            if (packetsID.find(hashcode) == packetsID.end()) {
                return;
            }

            std::size_t id = packetsID[hashcode];

            if (acknowledge) {
                size_t fingerprint = ((static_cast<size_t>(client.getId()) & 0xFF) << 56) | ((id & 0xFF) << 48) | (entityID & 0xFFFFFFFFFFFF);

                auto it = packetsbuffer.find(fingerprint);
                if (packetsbuffer.find(fingerprint) == packetsbuffer.end()) {
                    it = packetsbuffer.emplace(std::make_pair(fingerprint, PacketBuff(1))).first;
                }

                PacketBuff &pbuff = it->second;

                pbuff.buffer.clear();
                pbuff.buffer.writeBool(true);
                pbuff.buffer.writeULong(id+1);
                pbuff.buffer.writeULong(fingerprint);
                pbuff.buffer.writeCharBuffer(reinterpret_cast<const char *>(buffer.flush()), buffer.getSize());

                auto itpstatus = packetstatus.find(fingerprint);
                if (itpstatus == packetstatus.end()) {
                    itpstatus = packetstatus.emplace(std::make_pair(fingerprint, PacketInfo(fingerprint))).first;
                    itpstatus->second.client = &client;
                }

                PacketInfo &info = itpstatus->second;
                info.id = fingerprint;
                info.timestamp = 0;


                client.write(pbuff.buffer);
            } else {
                writeBuffer.clear();
                writeBuffer.writeBool(false);
                writeBuffer.writeULong(id+1);
                writeBuffer.writeULong(0);
                writeBuffer.writeCharBuffer(reinterpret_cast<const char *>(buffer.flush()), buffer.getSize());
                for (auto &client : clients) {
                    client->write(writeBuffer);
                }
            }
        }

        void processMessage(INetworkClient &client) {
            ByteBuffer &buffer = client.getBuffer();
            int err = 0;
            while (buffer.getSize() > 0) {
                bool acknowledge = buffer.readBool(&err);

                if (err) {
                    buffer.clear();
                    return;
                }

                size_t packetType = buffer.readULong(&err);
                if (err) {
                    buffer.clear();
                    return;
                }

                size_t fingerprint = buffer.readULong(&err);
                if (err) {
                    buffer.clear();
                    return;
                }

                if (acknowledge) {

                    if (packetType == 0) {
                        size_t subfingerprint = ((static_cast<size_t>(client.getId()) & 0xFF) << 56) | fingerprint;
                        if (packetstatus.erase(subfingerprint) == 1) {
                            auto it = packetsbuffer.find(fingerprint);
                            if (it != packetsbuffer.end()) {
                                it->second.count -= 1;
                                if (it->second.count == 0) {
                                    packetsbuffer.erase(it);
                                }
                            }
                        }
                        continue;
                    }
                }

                size_t buffSize = buffer.readUInt(&err);
                if (err) {
                    buffer.clear();
                    return;
                }

                if (packetHandlers.find(packetType - 1) == packetHandlers.end()) {
                    buffer.move(buffSize);
                    return;
                }

                auto &messageHandler = packetHandlers[packetType - 1];

                if (acknowledge) {
                    resbuffer.clear();
                    resbuffer.writeBool(true);
                    resbuffer.writeULong(0);
                    resbuffer.writeULong(fingerprint);
                    client.write(resbuffer);
                }

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

        size_t getEntityIDFromNetworkClient(INetworkClient &client) {
            return relatedEntityID[client.getId()];
        }
    protected:
    private:
        bool isClose = false;
        ByteBuffer buffer = {1024};
        ByteBuffer writeBuffer = {1024};
        ByteBuffer broadcastBuffer = {1024};
        ByteBuffer resbuffer = {1024};
        std::vector<std::unique_ptr<INetworkClient>> clients;
        std::map<unsigned int, std::chrono::high_resolution_clock::time_point> lastClientRes;
        std::map<unsigned int, unsigned int> relatedEntityID;
        std::chrono::high_resolution_clock::time_point lastTRequestStatus;
        std::size_t m_packetMaxSize;
        std::unordered_map<std::size_t, std::unique_ptr<IMessageHandler>> packetHandlers;
        std::unordered_map<std::size_t, std::size_t> packetsID;
        std::unordered_map<size_t, PacketInfo> packetstatus;
        std::unordered_map<size_t, PacketBuff> packetsbuffer;
};

#endif /* !NETWORKHANDLER_HPP_ */
