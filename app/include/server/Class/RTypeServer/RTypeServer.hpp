/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** RTypeServer
*/

#ifndef RTYPESERVER_HPP_
#define RTYPESERVER_HPP_

#include "server/Class/AServer/AServer.hpp"

class RTypeServer : AServer {
    public:
        RTypeServer();
        ~RTypeServer();

        void work() override;

    protected:
    private:
};

#endif /* !RTYPESERVER_HPP_ */