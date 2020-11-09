/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** main
*/

#include "server/Class/RTypeServer/RTypeServer.hpp"

int main(int ac, char *av[]) {
    // RTypeServer server;
    GameServer server;

    server.configure(3000);

    server.run();
    return (0);
}