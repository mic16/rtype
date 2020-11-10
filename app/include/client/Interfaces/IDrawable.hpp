/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** IDrawable
*/

#ifndef IDRAWABLE_HPP_
#define IDRAWABLE_HPP_

#include <SFML/Graphics.hpp>

class IDrawable {
    public:
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void setPosition(short x, short y) = 0;
        virtual void setPosition(sf::Vector2<short> position) = 0;
        virtual sf::Vector2<short> getPosition() = 0;
        virtual void setVisibility(bool visibility) = 0;
        virtual bool getVisibility() = 0;
};

#endif /* !IDRAWABLE_HPP_ */
