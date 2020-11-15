/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameServer
*/

#include "server/Class/GameServer/GameServer.hpp"
#include "shared/Packet/PlayerEnterRoomPacket.hpp"

GameServer::GameServer(Synchronizer &synchronizer, NetworkHandler &netwHandler) : UDPServer(),
    synchronizer(synchronizer), networkHandler(netwHandler)
{
}

GameServer::~GameServer()
{
}

void GameServer::work()
{
    handleConnection();
}

bool GameServer::handleConnection()
{
    acceptor->async_receive_from(boost::asio::buffer(client.getPacket(), 1024),
    client.m_endpoint,
    [this](const boost::system::error_code &errc,  std::size_t bytes_transferred) {
        if (!errc) {
            client.setClient(acceptor);
            // std::cout << "Client " << client.getAddress() << ':'
                // << client.getPort() << std::endl;
            if (players.find(client.getIdStr()) == players.end()) {
                UDPClient *newClient = new UDPClient(client);
                newClient->resetId();
                players.insert(std::pair<std::string, UDPClient *>(
                    client.getIdStr(),
                    newClient
                ));
                networkHandler.addClient(players.at(client.getIdStr()));
                synchronizer.getDoubleQueue().getWriteVector()->emplace_back(new PlayerEnterRoomPacket(players.at(client.getIdStr())));
                synchronizer.getDoubleQueue().update();
            } else { // message handling
                players.at(client.getIdStr())->getBuffer().append(client.getPacket(), bytes_transferred);
                networkHandler.processMessage(*players.at(client.getIdStr()));
            }
            this->handleConnection();
        } else {
            std::cout << "Failed connection client" << std::endl;
        }
    });
    return (true);
}

const UDPClient &GameServer::getClients() const
{
    return (client);
}