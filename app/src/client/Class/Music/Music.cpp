/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Music
*/

#include "client/Class/Music/Music.hpp"

Music::Music(std::string dir, short volume)
{
    boost::filesystem::path path(dir);
    boost::filesystem::directory_iterator end;
    this->volume = volume;
    isMenu = false;

    for (boost::filesystem::directory_iterator itr(path); itr != end; ++itr) {
        std::string file = itr->path().string();
        std::cout << file << std::endl;
        if (file.find(".ogg") != std::string::npos) {
            if (file.find("menu") != std::string::npos)
                if (!menu.openFromFile(file))
                    std::cout << "music " << file << " fail to load" << std::endl;
                else
                    std::cout << "music " << file << " loaded" << std::endl;
            else {
                std::unique_ptr<sf::Music> ptr = std::make_unique<sf::Music>();
                if (!ptr->openFromFile(file))
                    std::cout << "music " << file << " fail to load" << std::endl;
                else
                    std::cout << "music " << file << " loaded" << std::endl;
                list.push_back(std::move(ptr));
            }
        }
    }
}

Music::~Music()
{
}

void Music::playMenu()
{
    isMenu = true;
    menu.setVolume(volume);
    menu.setLoop(true);
    menu.play();
}

void Music::play()
{
    isMenu = false;
    srand (time(NULL));
    int rand = std::rand() % list.size();
    std::cout << "music :" << rand + 1<< std::endl;
    menu.stop();
    list[rand]->setVolume(volume);
    list[rand]->setLoop(true);
    list[rand]->play();
}