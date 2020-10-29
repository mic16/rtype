/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** IDrawable
*/

#ifndef IDRAWABLE_HPP_
#define IDRAWABLE_HPP_

class IDrawable {
    public:
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void setPosition(short x, short y) = 0;
};

#endif /* !IDRAWABLE_HPP_ */
