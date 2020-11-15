/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** RTypeServer
*/

#ifndef RTYPESERVER_HPP_
#define RTYPESERVER_HPP_

#include "lib/Server/TCPServer/TCPServer.hpp"
#include "server/Class/TCPClient/TCPClient.hpp"
#include "server/Class/GameServer/Game.hpp"
#include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/atomic.hpp>
#include <iostream>

class RTypeServer : public TCPServer {
    public:
        RTypeServer();
        ~RTypeServer();

        void work() override;

        unsigned int prepareNewClient();

        bool isClientConnected(const unsigned int client_id);
        bool isUsernameTaken(const std::string &username);
        bool isRoomNameExists(const std::string &roomname);
        bool disconnectClient(const unsigned int client_id);
        bool sendData(const unsigned int client_id);
        bool sendData(const ByteBuffer &buff, const std::vector<unsigned int> &clients_id);

        const std::map<unsigned int, std::unique_ptr<TCPClient>> &getClients() const;

        bool handleConnection();
        bool handleClient(const unsigned int client_id);

        void handleRequests(const unsigned int client_id);

        void responseLogin(const unsigned int client_id);
        void responseCreateRoom(const unsigned int client_id);
        void responseJoinRoom(const unsigned int client_id);
        void responseListPlayersInRoom(const std::string &roomname);
        void responseChangeUserStatus(const unsigned int client_id);
        void responseDisconnectRoom(const unsigned int client_id);
        void responseStartGame(const std::string &roomname);
        void quitClient(const unsigned int client_id);


        boost::lockfree::queue<Game *> gamesInProgress;
        boost::atomic<bool> done = false;
    private:
        std::map<unsigned int, std::unique_ptr<TCPClient>> clients;
        std::map<std::string, std::unique_ptr<Game>> games;
        boost::thread_group pool;
};

#endif /* !RTYPESERVER_HPP_ */
