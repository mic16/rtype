/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** main
*/

#include "client/Class/Window/Window.hpp"
#include "SFML/Graphics.hpp"
#include "client/Class/GameMenu/GameMenu.hpp"

int main(int argc, char **argv)
{
    // Window window;

    // return 0;
    // boost::asio::io_service ioservice;
    GameMenu menu;
    // UDPClient menu(ioservice, "127.0.0.1", "3000");

    return 
    menu.run();
}
