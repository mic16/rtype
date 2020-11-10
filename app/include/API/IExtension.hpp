/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** IExtension
*/

#ifndef IEXTENSION_HPP_
#define IEXTENSION_HPP_

#include "ECS/ECS.hpp"

class IExtension {
    public:
        virtual void onLoad(ECS &ecs) = 0;
    protected:
    private:
};

#endif /* !IEXTENSION_HPP_ */
