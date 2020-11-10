/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** ChangeUserStatus
*/

#include "server/Class/RTypeServer/RTypeServer.hpp"

void RTypeServer::responseJoinRoom(const unsigned int client_id)
{
    int err = 0;
    const char *roomname = clients[client_id]->getBuffer().readCharBuffer(nullptr, &err);

    clients[client_id]->getBuffer().clear();
    clients[client_id]->getBuffer().writeUInt(sizeof(int) + sizeof(bool));
    clients[client_id]->getBuffer().writeInt(res::Type::JoinRoom);
    if (err || !isRoomNameExists(roomname)) {
        std::cout << "Error on joinRoom." << std::endl;
        clients[client_id]->getBuffer().writeBool(false);
        sendData(client_id);
        return;
    }
    std::cout << "JoinRoom success." << std::endl;
    clients[client_id]->getBuffer().writeBool(true);
    games.at(roomname)->getLobby().join(client_id);
    sendData(client_id);
    responseListPlayersInRoom(roomname);
}

void RTypeServer::responseChangeUserStatus(const unsigned int client_id)
{
    int err = 0;
    const char *roomname = clients[client_id]->getBuffer().readCharBuffer(nullptr, &err);

    if (err || !isRoomNameExists(roomname)) {
        std::cout << "Error on ChangeUserStatus." << std::endl;
        return;
    }
    games.at(roomname)->getLobby().setStatus(client_id, !games.at(roomname)->getLobby().getStatus(client_id));
    std::cout << "ChangeUserStatus success." << std::endl;
    responseListPlayersInRoom(roomname);
    if (games.at(roomname)->getLobby().isReady()) {
        std::cout << "Game will start." << std::endl;
        responseStartGame(roomname);
    }
}

void RTypeServer::responseStartGame(const std::string &roomname)
{
    if (!isRoomNameExists(roomname)) return;
    ByteBuffer buff(16);

    const std::vector<unsigned int> &players_id = games.at(roomname)->getLobby().getPlayers();
    buff.writeUInt(sizeof(int));
    buff.writeInt(res::Type::StartGame);
    sendData(buff, players_id);
}