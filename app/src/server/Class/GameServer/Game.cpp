/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Game
*/

#include "server/Class/GameServer/Game.hpp"

Game::Game():
    lobby(Ladder::genId()),
    gameServer(networkHandler)
{
}

Game::~Game()
{
}

void Game::loadExtensions(std::vector<std::unique_ptr<IExtension>> &extensions) {

}

void Game::compile() {
    ecs.compile();
}

void Game::update() {
    auto now = std::chrono::high_resolution_clock::now();
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(lastTime - now);
    double delta = nanos.count() / 1000000000.0;

    lastTime = now;

    ecs.update(delta);
}

const server_info_t Game::setGameServer()
{
    server_info_t info;

    gameServer.configure();
    info.address = "127.0.0.1";
    info.port = gameServer.getPort();
    return (info);
}

void Game::startGame()
{
    gameServer.run();
}

Ladder &Game::getLobby()
{
    return (lobby);
}