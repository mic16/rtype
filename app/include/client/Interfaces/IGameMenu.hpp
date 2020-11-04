/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** IGameMenu
*/

#ifndef IGAMEMENU_HPP_
#define IGAMEMENU_HPP_

class IGameMenu {
    public:
        virtual int run() = 0;

        virtual void draw() = 0;
        virtual bool isOpen() = 0;

        virtual bool isUsernameValid() = 0;

        virtual void handleEvents() = 0;
        virtual void handleTextEntered() = 0;
        virtual void handleKeyReleased() = 0;

        virtual void handleDisplay() = 0;
        virtual void tryLogIn() = 0;
};

#endif /* !IGAMEMENU_HPP_ */