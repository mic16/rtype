/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** EntityAnimationManager
*/

#ifndef ENTITYANIMATIONMANAGER_HPP_
#define ENTITYANIMATIONMANAGER_HPP_

#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>

struct Animation {
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    sf::Vector2u startingImage;
    float totalTime = 0;
    float switchTime;
    sf::IntRect uvRect;
    bool reverse = false;
};

class EntityAnimationManager {
    public:
        EntityAnimationManager() {}
        ~EntityAnimationManager() {}

        void pushAnimation(size_t id, Animation *animation) {
            map.insert(std::make_pair(id, animation));
        }

        Animation *getAnimation(size_t id) {
            if (map.find(id) != map.end()) {
                return map.at(id).get();
            }
            return nullptr;
        }

    protected:
    private:
        std::unordered_map<size_t, std::unique_ptr<Animation>> map;
};

#endif /* !ENTITYANIMATIONMANAGER_HPP_ */
