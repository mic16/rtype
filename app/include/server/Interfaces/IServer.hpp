/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** IServer
*/

#ifndef ISERVER_HPP_
#define ISERVER_HPP_

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>

class IServer {
    public:
        virtual bool configure(const unsigned int port) = 0;
        virtual void work() = 0;
        virtual bool run() = 0;

        virtual unsigned int getPort() const = 0;
};

#endif /* !ISERVER_HPP_ */
