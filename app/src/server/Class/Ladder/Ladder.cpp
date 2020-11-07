/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Ladder
*/

#include "server/Class/Ladder/Ladder.hpp"

Ladder::Ladder(const unsigned int id, unsigned int maxPlayers):
    id(id), maxPlayers(maxPlayers)
{
}

Ladder::~Ladder()
{
}

unsigned int Ladder::genId()
{
    static unsigned int id = 0;

    id += 1;
    return (id);
}

unsigned int Ladder::getId() const
{
    return (id);
}

void Ladder::join(const unsigned int player_id)
{
    if (getNbPlayers() < getMaxPlayers())
        players.push_back(player_id);
}

const std::vector<unsigned int> &Ladder::getPlayers()
{
    return (players);
}

bool Ladder::disconnect(const unsigned int player_id)
{
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i] == player_id) {
            players.erase(players.begin() + i);
            return (true);
        }
    }
    return (false);
}

unsigned int Ladder::getMaxPlayers() const
{
    return (maxPlayers);
}

unsigned int Ladder::getNbPlayers() const
{
    return (players.size());
}