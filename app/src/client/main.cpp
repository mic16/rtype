/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** main
*/

#include "client/Class/Client/Client.hpp"
#include "client/Class/GameWindow/GameWindow.hpp"

int main(int argc, char **argv)
{
    Client client;
    GameWindow gameWindow;

    client.run();
    return 0;
}