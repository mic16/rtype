/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** createRoom
*/

#include "server/Class/RTypeServer/RTypeServer.hpp"

void RTypeServer::responseCreateRoom(const unsigned int client_id)
{
    int err = 0;
    const char *roomname = clients[client_id]->getBuffer().readCharBuffer(nullptr, &err);

    clients[client_id]->getBuffer().clear();
    clients[client_id]->getBuffer().writeUInt(sizeof(int) + sizeof(bool));
    clients[client_id]->getBuffer().writeInt(res::Type::CreateRoom);
    if (err || isRoomNameExists(roomname)) {
        std::cout << "Error on createRoom." << std::endl;
        clients[client_id]->getBuffer().writeBool(false);
        sendData(client_id);
        return;
    }
    std::cout << "CreateRoom success." << std::endl;
    clients[client_id]->getBuffer().writeBool(true);
    games.insert(std::pair<std::string, std::unique_ptr<Game>>(roomname, std::make_unique<Game>()));
    games.at(roomname)->getLobby().join(client_id);
    sendData(client_id);
    responseListPlayersInRoom(roomname);
}

bool RTypeServer::isRoomNameExists(const std::string &roomname)
{
    for (std::map<std::string, std::unique_ptr<Game>>::iterator it = games.begin(); it != games.end(); ++it) {
        if (it->first == roomname && !roomname.empty())
            return (true);
    }
    return (false);
}

void RTypeServer::responseListPlayersInRoom(const std::string &roomname)
{
    if (!isRoomNameExists(roomname)) return;
    ByteBuffer buff(1024);

    const std::vector<unsigned int> &players_id = games.at(roomname)->getLobby().getPlayers();
    unsigned int size_total = sizeof(int) + sizeof(unsigned int);
    for (size_t i = 0; i < players_id.size(); i++) {
        std::cout << players_id[i] << std::endl;
        size_total += clients[players_id[i]]->getUsername().size() + 1;
    }
    size_total += sizeof(unsigned int) * players_id.size() + sizeof(bool) * players_id.size();
    buff.writeUInt(size_total);
    buff.writeInt(res::Type::listPlayersInRoom);
    buff.writeUInt(players_id.size());
    for (size_t i = 0; i < players_id.size(); i++) {
        buff.writeCharBuffer(clients[players_id[i]]->getUsername().c_str());
        buff.writeBool(games.at(roomname)->getLobby().getStatus(players_id[i]));
    }
    sendData(buff, players_id);
}