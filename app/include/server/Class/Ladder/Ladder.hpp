/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Ladder
*/

#ifndef LADDER_HPP_
#define LADDER_HPP_

#include <vector>

class Ladder {
    public:
        Ladder(const unsigned int id, unsigned int maxPlayers = 4);
        ~Ladder();

        static unsigned int genId();

        unsigned int getId() const;
        unsigned int getMaxPlayers() const;
        unsigned int getNbPlayers() const;

        void join(const unsigned int player_id);
        bool disconnect(const unsigned int player_id);

        const std::vector<unsigned int> &getPlayers();
    private:
        const unsigned int id;
        std::vector<unsigned int> players;
        unsigned int maxPlayers;
};

#endif /* !LADDER_HPP_ */