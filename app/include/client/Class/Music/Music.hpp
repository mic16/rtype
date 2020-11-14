/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <vector>
#include <memory>
#include <time.h>

#include "SFML/Audio/Music.hpp"

class Music {
    public:
        Music(std::string path, short volume);
        ~Music();

        void playMenu();
        void play();
        bool getisMenu() const { return isMenu;};

    protected:
    private:
        std::vector<std::unique_ptr<sf::Music>> list;
        sf::Music menu;
        short volume;
        bool isMenu;
};

#endif /* !MUSIC_HPP_ */
