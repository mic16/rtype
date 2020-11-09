/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Background
*/

#include "client/Class/Background/Background.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

Background::Background(sf::RenderWindow &window) : window(window)
{
    texture.loadFromFile("app/assets/images/backgrounds/background_space.png");
    sprite.setTexture(texture);
    sprite.scale(4, 4);

    view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
    x = 0;
    y = 0;
}

Background::~Background()
{
}

void Background::update()
{
    x += 1;
}

void Background::draw()
{
    window.draw(sprite);
    view.reset(sf::FloatRect(x, y, 1000, 800));
    view.setCenter(500.f + x, 500.f);
    window.setView(view);
}

