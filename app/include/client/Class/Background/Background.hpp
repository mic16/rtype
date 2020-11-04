/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Background
*/

#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

#include <SFML/Graphics.hpp>
#include "client/Class/ADrawable/ADrawable.hpp"

class Background: public ADrawable {
    public:
        Background(sf::RenderWindow &window);
        Background();
        ~Background();
        void update();
        void draw();

    protected:
    private:
        sf::RenderWindow &window;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::View view;
        short speed;
};

#endif /* !BACKGROUND_HPP_ */
