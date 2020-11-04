/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** login
*/

#include "client/Class/TCPClient/TCPClient.hpp"

void TCPClient::handleLogIn()
{
    int err = 0;
    bool success = buffer.readBool(&err);
    if (err || !success) {
        std::cout << "LogIn error!" << std::endl;
        return;
    }
    std::cout << "LogIn success." << std::endl;
}