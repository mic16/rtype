/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** disconnect
*/

#include "server/Class/RTypeServer/RTypeServer.hpp"

void RTypeServer::responseDisconnectRoom(const unsigned int client_id)
{
    int err = 0;
    const char *roomname = clients[client_id]->getBuffer().readCharBuffer(nullptr, &err);

    clients[client_id]->getBuffer().clear();
    if (err || !isRoomNameExists(roomname)) {
        std::cout << "Error on DisconnectRoom." << std::endl;
        return;
    }
    if (games.at(roomname)->getLobby().disconnect(client_id))
        std::cout << "DisconnectRoom success." << std::endl;
    responseListPlayersInRoom(roomname);
}

void RTypeServer::quitClient(const unsigned int client_id)
{
    std::cout << "trying to close socket" << std::endl;
    clients[client_id]->m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    clients[client_id]->m_socket.close();
}