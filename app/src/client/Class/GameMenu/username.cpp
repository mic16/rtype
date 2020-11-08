/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** username
*/

#include "client/Class/GameMenu/GameMenu.hpp"

bool GameMenu::isNameValid(const std::string &name)
{
    if (name.length() < 3) return (false);
    for (size_t i = 0; i < name.length(); i++) {
        if (!std::isalnum(name[i]))
            return (false);
    }
    return (true);
}

const std::string &GameMenu::getUsername()
{
    return (username);
}