/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** events
*/

#include "client/Class/GameMenu/GameMenu.hpp"

void GameMenu::handleEvents()
{
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {
                handleTextEntered();
            }
        } else if (event.type == sf::Event::KeyPressed) {
            handleKeyPressed();
        } else if (event.type == sf::Event::KeyReleased) {
            handleKeyReleased();
        }
    }
}

void GameMenu::handleKeyPressed()
{
    if (gameEntities.isGamePlaying()) {
        switch (event.key.code) {
            case (sf::Keyboard::Z):
                isDirectionMaintained[gameEntities.DIRECTION::UP] = true;
                break;
            case (sf::Keyboard::Q):
                isDirectionMaintained[gameEntities.DIRECTION::LEFT] = true;
                break;
            case (sf::Keyboard::S):
                isDirectionMaintained[gameEntities.DIRECTION::DOWN] = true;
                break;
            case (sf::Keyboard::D):
                isDirectionMaintained[gameEntities.DIRECTION::RIGHT] = true;
                break;
            default:
                break;
        }
    }
}

void GameMenu::handleTextEntered()
{
    char charTyped = static_cast<char>(event.text.unicode);

    if (std::isalnum(charTyped)) {
        if (getScene() == sceneName::LOGIN) {
            if (username == "...") {
                username = "";
            }
            if (username.length() < 16)
                username += charTyped;
            setDrawableTextStr(sceneName::LOGIN, "usernameInput", username);
            setDrawableTextStr(sceneName::MENU, "username", username);
        } else if (getScene() == sceneName::CREATE || getScene() == sceneName::JOIN) {
            if (roomname == "...") {
                roomname = "";
            }
            if (roomname.length() < 16)
                roomname += charTyped;
            setDrawableTextStr(getScene(), "roomnameInput", roomname);
            setDrawableTextStr(sceneName::ROOM, "roomname", roomname);
        }
    }
}

void GameMenu::handleKeyReleased()
{
    if (gameEntities.isGamePlaying()) {
        switch (event.key.code) {
            case (sf::Keyboard::Z):
                isDirectionMaintained[gameEntities.DIRECTION::UP] = false;
                break;
            case (sf::Keyboard::Q):
                isDirectionMaintained[gameEntities.DIRECTION::LEFT] = false;
                break;
            case (sf::Keyboard::S):
                isDirectionMaintained[gameEntities.DIRECTION::DOWN] = false;
                break;
            case (sf::Keyboard::D):
                isDirectionMaintained[gameEntities.DIRECTION::RIGHT] = false;
                break;
            default:
                break;
        }
    } else {
        if (event.key.code == sf::Keyboard::Backspace) {
            if (getScene() == sceneName::LOGIN) {
                if (username.length() > 0) {
                    username.erase(username.size() - 1, 1);
                    setDrawableTextStr(sceneName::LOGIN, "usernameInput", username);
                    setDrawableTextStr(sceneName::MENU, "username", username);
                }
            } else if (getScene() == sceneName::CREATE || getScene() == sceneName::JOIN) {
                if (roomname.length() > 0) {
                    roomname.erase(roomname.size() - 1, 1);
                    setDrawableTextStr(getScene(), "roomnameInput", roomname);
                    setDrawableTextStr(sceneName::ROOM, "roomname", roomname);
                }
            }
        } else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
            if (getScene() == sceneName::LOGIN) {
                if (isNameValid(username)) {
                    tryLogIn();
                }
            } else if (getScene() == sceneName::MENU) {
                if (actualButton == menuButton::B_CREATE) {
                    setScene(sceneName::CREATE);
                } else if (actualButton == menuButton::B_JOIN) {
                    setScene(sceneName::JOIN);
                }
            } else if (getScene() == sceneName::CREATE) {
                tryCreateRoom();
            } else if (getScene() == sceneName::JOIN) {
                tryJoinRoom();
            } else if (getScene() == sceneName::ROOM) {
                tryChangeUserStatus();
            }
        } else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Up) {
            if (getScene() == sceneName::MENU) {
                dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)[menuButtons[actualButton]].get())->setFillColor(sf::Color::White);
                actualButton = actualButton == menuButton::B_CREATE ? menuButton::B_JOIN : menuButton::B_CREATE;
                dynamic_cast<sf::Text *>(modDrawables.at(sceneName::MENU)[menuButtons[actualButton]].get())->setFillColor(sf::Color::Yellow);
            }
        } else if (event.key.code == sf::Keyboard::Escape) {
            if (getScene() == sceneName::ROOM) {
            
            }
            setScene(sceneName::MENU);
        }
    }
}