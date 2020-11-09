/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameEntities
*/

#ifndef GAMEENTITIES_HPP_
#define GAMEENTITIES_HPP_

#include "SFML/Graphics.hpp"
#include "ECS/ECS.hpp"

#include <vector>
#include <fstream>
#include <string>

struct Position {
    float x;
    float y;
};

struct Velocity {
    short vx;
    short vy;
    float speed;
};

struct Drawable {
    bool visible;
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Sprite> sprite;
};

class GameEntities {
    public:
        GameEntities();
        ~GameEntities();
        void init();
        void update();
        void setWindow(std::shared_ptr<sf::RenderWindow> window) { this->window = window; };
        std::shared_ptr<sf::RenderWindow> getWindow() { return window; };
        ECS getEcs() { return ecs; };

    protected:
    private:
        void loadResources(std::string filename);
    
        std::shared_ptr<sf::RenderWindow> window;
        std::vector<Drawable> resources;
        ECS ecs;
};

#endif /* !GAMEENTITIES_HPP_ */