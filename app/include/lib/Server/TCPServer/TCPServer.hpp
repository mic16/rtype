/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** TCPServer
*/

#ifndef TCPSERVER_HPP_
#define TCPSERVER_HPP_

#include "lib/Interfaces/IServer.hpp"

class TCPServer : public IServer {
    public:
        TCPServer();
        ~TCPServer();

        bool configure(const unsigned int port);
        virtual void work();

        unsigned int getPort() const;

        bool run();
    protected:
        boost::asio::io_service ioService;
        std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;
        unsigned int port;
};

#endif /* !TCPSERVER_HPP_ */