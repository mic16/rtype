/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "lib/SFML.hpp"
#include "lib/Utility.hpp"

#include "client/Class/Animation/Animation.hpp"

class Player {
    public:
        Player();
        ~Player();

        // sf::ConvexShape getShape();
        Animation *getPlayerAnimation();
        sf::RectangleShape *getPlayerShape();
        void setPosition(float x, float y);

    private:
        // sf::ConvexShape convex;
        std::shared_ptr<sf::RectangleShape> playerShape;
        std::shared_ptr<sf::Texture> playerTexture;
        std::shared_ptr<Animation> animation;
};

#endif /* !PLAYER_HPP_ */