/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Game
*/

#include "server/Class/GameServer/Game.hpp"

Game::Game():
    lobby(Ladder::genId())
{
}

Game::~Game()
{
}

void Game::loadExtensions(std::vector<std::unique_ptr<IExtension>> &extensions) {

}

void Game::compile() {

}

void Game::update() {
    auto now = std::chrono::high_resolution_clock::now();
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(lastTime - now);
    double delta = nanos.count() / 1000000000.0;

    lastTime = now;

    ecs.update(delta);
}


Ladder &Game::getLobby()
{
    return (lobby);
}