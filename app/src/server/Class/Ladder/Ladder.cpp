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
    if (getNbPlayers() < getMaxPlayers()) {
        players.push_back(player_id);
        status.insert(std::pair<unsigned int, bool>(player_id, false));
    }
}

const std::vector<unsigned int> &Ladder::getPlayers()
{
    return (players);
}

void Ladder::setStatus(unsigned int player_id, bool newStatus)
{
    if (status.find(player_id) != status.end())
        status.at(player_id) = newStatus;
}

bool Ladder::getStatus(unsigned int player_id) const
{
    if (status.find(player_id) != status.end())
        return (status.at(player_id));
    return (false);
}

bool Ladder::disconnect(const unsigned int player_id)
{
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i] == player_id) {
            players.erase(players.begin() + i);
            status.erase(player_id);
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

bool Ladder::isReady() const
{
    for (std::map<unsigned int, bool>::const_iterator it = status.cbegin(); it != status.cend(); ++it) {
        if (!it->second)
            return (false);
    }
    return (true);
}