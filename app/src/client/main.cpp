/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** main
*/

#include "SFML/Graphics.hpp"
#include "Class/Window.hpp"
#include "client/Class/UDPClient/UDPClient.hpp"

int main()
{
    boost::asio::io_service io_service;
	UDPClient client(io_service, "localhost", "3000");

	client.send("Hello, World!");
}