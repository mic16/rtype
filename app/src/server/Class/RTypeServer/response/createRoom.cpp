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
    const char *roomname = clients[client_id]->getBuffer().readCharBuffer(&err);

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
    rooms.insert(std::pair<std::string, std::unique_ptr<Ladder>>(roomname, std::make_unique<Ladder>(Ladder::genId())));
    rooms.at(roomname)->join(client_id);
    sendData(client_id);
}

bool RTypeServer::isRoomNameExists(const std::string &roomname)
{
    for (std::map<std::string, std::unique_ptr<Ladder>>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
        if (it->first == roomname && !roomname.empty())
            return (true);
    }
    return (false);
}