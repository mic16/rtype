/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "client/Interfaces/IDrawable.hpp"

class ADrawable: public IDrawable {
    public:
        virtual void update() = 0;
        virtual void draw() = 0 ;
    
        void setPosition(short x, short y);
        void setPosition(sf::Vector2<short> position);
        sf::Vector2<short> getPosition();
    
        void setVisibility(bool visibility);
        bool getVisibility();

    
    protected:
        short x;
        short y;
        bool visibility;
};

#endif /* !DRAWABLE_HPP_ */
