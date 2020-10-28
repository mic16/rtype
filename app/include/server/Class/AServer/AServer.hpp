/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** AServer
*/

#ifndef ASERVER_HPP_
#define ASERVER_HPP_

#include "server/Interfaces/IServer.hpp"

class AServer : IServer {
    public:
        AServer();
        ~AServer();

        bool configure(const unsigned int port);
        virtual void work();

        bool run();
    protected:
        boost::asio::io_service ioService;
        std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;
        std::string address;
        unsigned int port;
};

#endif /* !ASERVER_HPP_ */