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
    sf::Texture texture;
    sf::Sprite sprite;
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
    sf::Vector2u currentImage;
    sf::Vector2u startingImage;
    float totalTime = 0;
    float switchTime;
    sf::IntRect uvRect;
    bool reverse = false;
};

class GameEntities {
    public:
        GameEntities(sf::RenderWindow &window);
        ~GameEntities();
        void init();
        sf::RenderWindow &getWindow() { return window; };
        ECS getEcs() { return ecs; };
        void update(bool *isDirectionMaintained, float deltaTime);

        void createPlayer(int nbOfPlayers, sf::Vector2f position, sf::Vector2u totalFrames, sf::Vector2u startingFrame, 
            float timeToSwitchFrames, sf::Vector2u textureSize, bool reverse, sf::Texture texture, sf::Sprite sprite);
        void createBackground(sf::Texture texture, sf::Sprite sprite);

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
        sf::RenderWindow &window;
        std::vector<Drawable> resources;
        ECS ecs;
        bool isDirectionMaintained[4];
        int row = 0;
        float deltaTime = 0.0f;
        bool gamePlaying = false;
};

#endif /* !GAMEENTITIES_HPP_ */