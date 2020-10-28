/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** main
*/

#include "server/Class/AServer/AServer.hpp"

int main(int ac, char *av[]) {
    AServer server;

    server.configure(3000);

    server.run();
    return (0);
}