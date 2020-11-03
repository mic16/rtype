/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include "lib/SFML.hpp"
#include "lib/Utility.hpp"

class Animation {
    public:
        Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime);
        ~Animation();

        void update(int row, float deltaTime, bool up, bool down);
        sf::IntRect getUvRect();

    private:
        sf::Vector2u imageCount;
        sf::Vector2i currentImage;
        float totalTime = 0;
        float switchTime;
        sf::IntRect uvRect;
        bool reverse = false;
};

#endif /* !ANIMATION_HPP_ */