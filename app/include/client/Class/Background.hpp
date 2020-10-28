/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Background
*/

#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

#include <SFML/Graphics.hpp>
#include "client/Interfaces/Drawable.hpp"

class Background: public Drawable {
    public:
        Background(sf::RenderWindow window);
        ~Background();


    protected:
    private:
        sf::RenderWindow window;
};

#endif /* !BACKGROUND_HPP_ */
