/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

class Drawable {
    public:
        virtual void update() = 0;
        virtual void draw() = 0;
        void setPosition(short x, short y);
    
    protected:
        short x;
        short y;
};

#endif /* !DRAWABLE_HPP_ */
