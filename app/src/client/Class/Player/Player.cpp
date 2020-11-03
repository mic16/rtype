/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Player
*/

#include "client/Class/Player/Player.hpp"

Player::Player()
{
    // convex.setPointCount(7);

    // convex.setPoint(0, sf::Vector2f(0, 0));
    // convex.setPoint(1, sf::Vector2f(100, 0));
    // convex.setPoint(2, sf::Vector2f(150, 30));
    // convex.setPoint(3, sf::Vector2f(150, 50));
    // convex.setPoint(4, sf::Vector2f(100, 70));
    // convex.setPoint(4, sf::Vector2f(50, 70));
    // convex.setPoint(4, sf::Vector2f(0, 60));
    // convex.setFillColor(sf::Color::Blue);
    // convex.setPosition(100, 100);

    playerShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(50, 50));
    playerShape.get()->setPosition(200, 200);
    playerTexture = std::make_shared<sf::Texture>();
    playerTexture.get()->loadFromFile("app/assets/sprites/r-typesheet42.png");
    playerShape.get()->setTexture(playerTexture.get());
    animation = std::make_shared<Animation>(playerTexture.get(), sf::Vector2u(5, 5), 0.05f);
}

Player::~Player()
{
}

Animation *Player::getPlayerAnimation()
{
    return (&animation.get()[0]);
}

sf::RectangleShape *Player::getPlayerShape()
{
    return (&playerShape.get()[0]);
}

void Player::setPosition(float x, float y)
{
    playerShape.get()->setPosition(playerShape.get()->getPosition().x + x, playerShape.get()->getPosition().y + y);
}

// sf::ConvexShape Player::getShape() { return (convex); }