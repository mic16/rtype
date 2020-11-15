/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** UDPClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include "client/Class/UDPClient/RemoteClient.hpp"
#include "lib/Network/NetworkHandler.hpp"

class UDPClient {
    public:
        UDPClient(boost::asio::io_context &io_service, const std::string &host, const std::string &port, NetworkHandler &networkHandler);
        ~UDPClient();

        void work();
        void run();

        void connect();

        void close() {
            client->socket.close();
            client->ioService.stop();
        }

    private:
        RemoteClient *client;
        NetworkHandler &networkHandler;
};

#endif /* !UDPCLIENT_HPP_ */
