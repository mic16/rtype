/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Ladder
*/

#ifndef LADDER_HPP_
#define LADDER_HPP_

#include <map>
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
        void setStatus(unsigned int, bool newStatus);
        bool getStatus(unsigned int) const;

        bool isReady() const;
    private:
        const unsigned int id;
        std::vector<unsigned int> players;
        std::map<unsigned int, bool> status;
        unsigned int maxPlayers;
};

#endif /* !LADDER_HPP_ */