/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Background
*/

#include "client/Class/Background/Background.hpp"

Background::Background(sf::RenderWindow &window, float speed) : window(window)
{
    texture.loadFromFile("app/assets/images/backgrounds/space.png");
    sprite.setTexture(texture);

    sprite.setScale(4, 4);
    position.x = 0;
    position.y = 0;
    this->speed = speed;
}

Background::~Background()
{
}

void Background::update(float delta)
{ 
    position.x += -1 * speed * delta;

    if (position.x <= -4904)
        position.x = position.x + 4904;

    sprite.setPosition(position.x, position.y);
}

void Background::draw()
{
    window.draw(sprite);
}