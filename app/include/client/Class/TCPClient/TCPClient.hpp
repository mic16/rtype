/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** TCPClient
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_

#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include "client/Class/UDPClient/UDPClient.hpp"
#include "client/Class/Exceptions/EConnection.hpp"
#include "client/Interfaces/IGameMenu.hpp"
#include "lib/ByteBuffer/ByteBuffer.hpp"
#include "lib/request.h"
#include "lib/response.h"

class TCPClient {
    public:
        TCPClient(IGameMenu *gameMenu);
        ~TCPClient();

        void run();
        void join();
        void connectTo(const boost::asio::ip::tcp::endpoint &endpoint);

        void handleData();
        void sendData(const unsigned char *buff, const size_t buffLen);

        void handleResponses();

        void handleLogIn();
        void handleCreateRoom();
        void handleJoinRoom();
        void handleListPlayersInRoom();
        void handleInfoServer();

        void closeClientServer() { if (gameClient.get() != nullptr && menu->getScene() != sceneName::END) { gameClient->close(); } };

        std::unique_ptr<UDPClient> &getGameClient();
    private:
        boost::asio::io_context ioService;
        boost::asio::ip::tcp::socket socket;
        boost::asio::ip::tcp::endpoint endpoint;
        char *m_packet = nullptr;
        IGameMenu *menu;
        ByteBuffer buffer;
        std::unique_ptr<UDPClient> gameClient;

        std::unique_ptr<boost::thread> t;
};

#endif /* !TCPCLIENT_HPP_ */

