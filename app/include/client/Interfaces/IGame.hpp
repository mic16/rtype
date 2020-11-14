/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

class IGame {
    public:
        virtual void setPlayerID(size_t id) = 0;
        virtual size_t getPlayerID() = 0;
};


#endif /* !IGAME_HPP_ */
