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
    bool load(std::string filename)
    {
        return (soundBuffer.loadFromFile(filename));
    }

    void update()
    {
        for (int i = 0; i < soundInstances.size(); i++) {
            if (soundInstances[i].getStatus() == sf::Sound::Stopped) {
                soundInstances.erase(soundInstances.begin() + i);
                i--;
            }
        }
    }

    void play(float volume)
    {
        sf::Sound sound = sf::Sound(soundBuffer);

        sound.setVolume(volume);
        soundInstances.push_back(sound);
        soundInstances.back().play();
    }

private:
    sf::SoundBuffer soundBuffer;
    std::deque<sf::Sound> soundInstances;
};