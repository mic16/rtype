/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Drawable
*/

#include "client/Class/ADrawable/ADrawable.hpp"

void ADrawable::setPosition(short x, short y)
{
    this->x = x;
    this->y = y;
}

void ADrawable::setPosition(sf::Vector2<short> position)
{
    x = position.x;
    y = position.y;
}

sf::Vector2<short> ADrawable::getPosition()
{
    sf::Vector2<short> position(x, y);

    return position;
}

void ADrawable::setVisibility(bool visibility)
{
    this->visibility = visibility;
}

bool ADrawable::getVisibility()
{
    return visibility;
}