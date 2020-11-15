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

#include "shared/Components/Components.hpp"
#include "shared/Synchronizer/Synchronizer.hpp"
#include "EntitySpriteManager.hpp"
#include "EntityAnimationManager.hpp"
#include "client/Interfaces/IGame.hpp"
#include "EntityAnimationManager.hpp"

#include "client/Class/Sound/Sound.hpp"

struct Drawable {
    bool visible;
    sf::Sprite *sprite;
    sf::IntRect uvRect;
};

class GameEntities {
    public:
        GameEntities(IGame *gameMenu, sf::RenderWindow &window, Synchronizer &synchronizer, EntitySpriteManager &spriteManager, EntityAnimationManager &animationManager);
        ~GameEntities();
        void init();
        sf::RenderWindow &getWindow() { return window; };
        ECS &getECS() { return ecs; };
        Synchronizer &getSynchronizer() {return synchronizer; }
        void update(bool *isDirectionMaintained, float deltaTime);

        void createPlayer(int nbOfPlayers, sf::Vector2f position, sf::Vector2u totalFrames, sf::Vector2u startingFrame,
            float timeToSwitchFrames, sf::Vector2u textureSize, bool reverse, sf::Sprite *sprite, size_t id);
        void createEnemy(sf::Vector2f position, sf::Vector2u totalFrames, sf::Vector2u startingFrame,
            float timeToSwitchFrames, sf::Vector2u textureSize, bool reverse, sf::Sprite *sprite, size_t id);

        enum DIRECTION {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        void setDead() { dead = true; }
        bool getDead() { return (dead); }

        bool isGamePlaying() { return (gamePlaying); };
        void setGamePlaying(bool gamePlaying) { this->gamePlaying = gamePlaying; };
        IGame *getGameMenu() { return gameMenu; }

        Sound &getExplosionSound() { return (explosionSound); }

        bool getEnd() { return end; }

    protected:
    private:
        IGame *gameMenu;
        sf::RenderWindow &window;
        std::vector<Drawable> resources;
        ECS ecs;
        bool isDirectionMaintained[4];
        bool gamePlaying = false;
        Synchronizer &synchronizer;
        EntitySpriteManager &spriteManager;
        EntityAnimationManager &animationManager;

        bool dead = false;
        Sound explosionSound;
        bool end = false;
};

#endif /* !GAMEENTITIES_HPP_ */