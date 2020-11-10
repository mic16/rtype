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

struct Status {
    bool isAlive;
    size_t hp;
    size_t maxhp;
};

struct ProjectileStats {
    size_t damage;
    uint8_t type;
};

struct Hitbox {
    size_t x;
    size_t y;
    size_t w;
    size_t h;
};

struct Animation {
    sf::Vector2u imageCount;
    sf::Vector2i currentImage;
    float totalTime = 0;
    float switchTime;
    sf::IntRect uvRect;
    bool reverse = false;
};

class GameEntities {
    public:
        GameEntities(std::shared_ptr<sf::RenderWindow> window);
        ~GameEntities();
        void init();
        std::shared_ptr<sf::RenderWindow> getWindow() { return window; };
        ECS getEcs() { return ecs; };

        void update(bool *isDirectionMaintained, float deltaTime, std::shared_ptr<sf::RenderWindow> window);

        enum DIRECTION {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        bool isGamePlaying() { return (gamePlaying); };
        void setGamePlaying(bool gamePlaying) { this->gamePlaying = gamePlaying; };

    protected:
    private:
        void loadResources(std::string filename);
        std::shared_ptr<sf::RenderWindow> window;
        std::vector<Drawable> resources;
        ECS ecs;
        bool isDirectionMaintained[4];
        int row = 0;
        float deltaTime = 0.0f;
        bool gamePlaying = false;
};

#endif /* !GAMEENTITIES_HPP_ */