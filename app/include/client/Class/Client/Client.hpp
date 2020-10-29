/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <boost/asio.hpp>
#include <iostream>
#include <vector>

class Client {
    public:
        Client();
        ~Client();

        bool isRunning() const;

        void run();
        void connectTo(const boost::asio::ip::tcp::endpoint &endpoint);
        void handleData();
    private:
        bool running;
        boost::asio::io_service ioService;
        boost::asio::ip::tcp::socket socket;
        boost::asio::ip::tcp::endpoint endpoint;
        char msg[17];
};

#endif /* !CLIENT_HPP_ */
