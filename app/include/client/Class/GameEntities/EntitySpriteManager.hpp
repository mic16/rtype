/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** EntitySpriteManager
*/

#ifndef ENTITYSPRITEMANAGER_HPP_
#define ENTITYSPRITEMANAGER_HPP_

#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>

class EntitySpriteManager {
    public:
        EntitySpriteManager() {}
        ~EntitySpriteManager() {}

        void pushSprite(size_t id, sf::Sprite *sprite) {
            map.insert(std::make_pair(id, sprite));
        }

        sf::Sprite *getSprite(size_t id) {
            if (map.find(id) != map.end()) {
                return map.at(id).get();
            }
            return nullptr;
        }

    protected:
    private:
        std::unordered_map<size_t, std::unique_ptr<sf::Sprite>> map;
};

#endif /* !ENTITYSPRITEMANAGER_HPP_ */
