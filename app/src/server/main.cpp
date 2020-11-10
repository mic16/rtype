/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** main
*/

#include "server/Class/RTypeServer/RTypeServer.hpp"
#include "lib/Network/NetworkHandler.hpp"

class Packet : public IPacket {
public:
    Packet() {

    }

    ~Packet() {

    }

    void fromBuffer(ByteBuffer &buffer) {

    }

    void toBuffer(ByteBuffer &buffer) {

    }
};

class MessageHandler : public AMessageHandler<Packet> {
    public:
    MessageHandler() {}
    ~MessageHandler() {}

    void onMessage(Packet &packet) {

    }
};

int main(int ac, char *av[]) {
    RTypeServer server;
    // GameServer server;

    server.configure(3000);

    server.run();
    return (0);
}