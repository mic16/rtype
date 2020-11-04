/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** username
*/

#include "client/Class/GameMenu/GameMenu.hpp"

bool GameMenu::isUsernameValid()
{
    if (username.length() < 3) return (false);
    for (size_t i = 0; i < username.length(); i++) {
        if (!std::isalnum(username[i]))
            return (false);
    }
    return (true);
}