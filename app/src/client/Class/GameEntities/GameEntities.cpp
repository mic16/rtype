/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameEntities
*/

#include "client/Class/GameEntities/GameEntities.hpp"
#include <boost/algorithm/string.hpp>

GameEntities::GameEntities(sf::RenderWindow &window) : window(window)
{
    for (int i = 0; i != 4 ; i++)
        isDirectionMaintained[i] = false;
}

void GameEntities::init()
{
    ecs.newEntityModel<Position, Animation, Drawable, EntityId>("Player")
        .addTags({ "PlayerControlled", "Drawable" })
        .finish();

    ecs.newSystem<Position, Drawable>("Movement")
        .withTags({ "PlayerControlled" })
        .each([this](float delta, EntityIterator<Position, Drawable> &entity) {
                while (entity.hasNext()) {
                    entity.next();

                    Position* position = entity.getComponent<Position>(0);
                    Drawable* drawable = entity.getComponent<Drawable>(1);

                    if (isDirectionMaintained[DIRECTION::UP])
                        position->y -= 100 * delta;
                    if (isDirectionMaintained[DIRECTION::DOWN])
                        position->y += 100 * delta;
                    if (isDirectionMaintained[DIRECTION::LEFT])
                        position->x -= 100 * delta;
                    if (isDirectionMaintained[DIRECTION::RIGHT]) {
                        position->x += 100 * delta;
                    }
                    
                    drawable->sprite.setPosition(position->x, position->y);
                }
            })
        .finish();

        ecs.newSystem<Animation, Drawable>("AnimatePlayer")
        .withTags({ "PlayerControlled" })
        .each([this](float delta, EntityIterator<Animation, Drawable> &entity){
                while (entity.hasNext()) {
                    entity.next();

                    Animation *animation = entity.getComponent<Animation>(0);
                    Drawable *drawable = entity.getComponent<Drawable>(1);

                    animation->currentImage.y = row;
                    animation->totalTime += deltaTime;
                    if (animation->totalTime >= animation->switchTime) {
                        animation->totalTime -= animation->switchTime;
                        if (isDirectionMaintained[DIRECTION::UP] && animation->currentImage.x < animation->imageCount.x - 1)
                            animation->currentImage.x++;
                        else if (isDirectionMaintained[DIRECTION::DOWN] && animation->currentImage.x > 0)
                            animation->currentImage.x--;
                        else if (!isDirectionMaintained[DIRECTION::UP] && !isDirectionMaintained[DIRECTION::DOWN]) {
                            if (animation->currentImage.x > animation->startingImage.x)
                                animation->currentImage.x--;
                            else if (animation->currentImage.x < animation->startingImage.x)
                                animation->currentImage.x++;
                        }
                    }
                    animation->uvRect.left = animation->currentImage.x * animation->uvRect.width;
                    animation->uvRect.top = animation->currentImage.y * animation->uvRect.height;
                    drawable->sprite.setTextureRect(animation->uvRect);
                }
            })
        .finish();

        ecs.newSystem<Drawable>("Draw")
        .withTags({ "Drawable" })
        .each([this](float delta, EntityIterator<Drawable> &entity) {
            while (entity.hasNext()) {
                entity.next();

                Drawable *drawable = entity.getComponent<Drawable>(0);
                this->window.draw(drawable->sprite);
            }
        })
        .finish();

    ecs.compile();
}

GameEntities::~GameEntities()
{
}

void GameEntities::createPlayer(int nbOfPlayers, sf::Vector2f position, sf::Vector2u totalFrames, sf::Vector2u startingFrame,
    float timeToSwitchFrames, sf::Vector2u textureSize, bool reverse, sf::Texture texture, sf::Sprite sprite, size_t id)
{
    auto playerGenerator = ecs.getEntityGenerator("Player");
    playerGenerator.reserve(nbOfPlayers);
    playerGenerator
        .instanciate(nbOfPlayers, Position{ position.x, position.y },
        Animation{ totalFrames, startingFrame, startingFrame, 0, timeToSwitchFrames,
        sf::IntRect(0, 0, textureSize.x / totalFrames.x, textureSize.y / totalFrames.y),
        reverse }, Drawable{ true, texture, sprite }, EntityId{ id });
}

void GameEntities::update(bool *isDirectionMaintained, float deltaTime)
{
    for (int i = 0; i != 4; i++)
        this->isDirectionMaintained[i] = isDirectionMaintained[i];
    this->deltaTime = deltaTime;
    ecs.update(deltaTime);
}