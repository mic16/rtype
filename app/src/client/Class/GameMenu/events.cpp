/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** events
*/

#include "client/Class/GameMenu/GameMenu.hpp"

void GameMenu::handleEvents()
{
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        } else if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {
                handleTextEntered();
            }
        } else if (event.type == sf::Event::KeyReleased) {
            handleKeyReleased();
        }
    }
}

void GameMenu::handleTextEntered()
{
    char charTyped = static_cast<char>(event.text.unicode);

    if (std::isalnum(charTyped)) {
        if (scene == sceneName::LOGIN) {
            if (username == "...") {
                username = "";
            }
            if (username.length() < 16)
                username += charTyped;
            dynamic_cast<sf::Text *>(modDrawables.at(sceneName::LOGIN)["usernameInput"].get())->setString(username);
        }
    }
}

void GameMenu::handleKeyReleased()
{
    if (event.key.code == sf::Keyboard::Backspace) {
        if (scene == sceneName::LOGIN) {
            if (username.length() > 0) {
                username.erase(username.size() - 1, 1);
                dynamic_cast<sf::Text *>(modDrawables.at(sceneName::LOGIN)["usernameInput"].get())->setString(username);
            }
        }
    } else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
        if (isUsernameValid()) {
            tryLogIn();
        }
    }
}