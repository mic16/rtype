/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Sound
*/

#include <SFML/Audio.hpp>
#include <iostream>
#include <deque>


class Sound
{
public:
    Sound() {}
    ~Sound() {}

    bool load(std::string filename)
    {
        return (soundBuffer.loadFromFile(filename));
    }

    void update()
    {
        auto it = soundInstances.begin();

        while (it != soundInstances.end()) {
            if ((*it)->getStatus() == sf::Sound::Stopped) {
                soundInstances.erase(it);
                continue;
            }
            it++;
        }
    }

    void play(float volume)
    {
        soundInstances.emplace_back(new sf::Sound(soundBuffer));
        std::unique_ptr<sf::Sound> &sound = soundInstances.back();
        sound->setVolume(volume);
        sound->play();
    }

private:
    sf::SoundBuffer soundBuffer;
    std::vector<std::unique_ptr<sf::Sound>> soundInstances;
};