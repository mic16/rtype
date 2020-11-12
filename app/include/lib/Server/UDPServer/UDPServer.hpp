/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** UDPServer
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include "lib/Interfaces/IServer.hpp"

class UDPServer : public IServer {
    public:
        UDPServer();
        ~UDPServer();

        bool configure(const unsigned int port = 0);
        virtual void work();

        unsigned int getPort() const;

        bool run();
        void join();
    protected:
        boost::asio::io_context ioService;
        std::shared_ptr<boost::asio::ip::udp::socket> acceptor;
        unsigned int port;
        std::unique_ptr<boost::thread> m_thread;
};

#endif /* !UDPSERVER_HPP_ */