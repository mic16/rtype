/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameEntities
*/

#include "client/Class/GameEntities/GameEntities.hpp"
#include "shared/Packet/SpawnPacket.hpp"
#include "shared/Packet/InstanciatePlayerPacket.hpp"
#include <boost/algorithm/string.hpp>
#include "shared/Structs/EntityType.hpp"

GameEntities::GameEntities(IGame *gameMenu, sf::RenderWindow &window, Synchronizer &synchronizer, EntitySpriteManager &spriteManager, EntityAnimationManager &animationManager) : gameMenu(gameMenu), window(window), synchronizer(synchronizer), spriteManager(spriteManager), animationManager(animationManager)
{
    for (int i = 0; i != 4 ; i++)
        isDirectionMaintained[i] = false;
    this->getExplosionSound().load("app/assets/sounds/explosion.wav");
}

void GameEntities::init()
{
    ecs.newEntityModel<Position, Animation, EntityID, Drawable>("Player")
        .addTags({ "PlayerControlled", "Drawable" })
        .finish();

    ecs.newEntityModel<Position, Animation, EntityID, Drawable>("Entity")
        .addTags({"Entity", "Drawable"})
        .finish();

    ecs.newEntityModel<Position, Animation, EntityID, Drawable>("Wall")
        .addTags({"Wall", "Drawable"})
        .finish();

    ecs.newSystem<Position, EntityID>("UpdateEntities")
    .each([this](float delta, EntityIterator<Position, EntityID> &entity) {
        if (this->getSynchronizer().getDoubleMap().isReadClose())
            return;

        Synchronizer &synchronizer = this->getSynchronizer();
        auto &readMap = synchronizer.getDoubleMap().getReadMap();

        while (entity.hasNext()) {
            entity.next();

            Position *position = entity.getComponent<Position>(0);
            EntityID *entityID = entity.getComponent<EntityID>(1);

            if (readMap->find(entityID->id) != readMap->end()) {
                PacketData &data = readMap->at(entityID->id);

                if (!data.isAlive) {
                    entity.remove();
                    if (entityID->id == getGameMenu()->getPlayerID()) {
                        this->getExplosionSound().play(10.0f);
                        this->setDead();
                    }
                    continue;
                }

                position->x = data.x;
                position->y = data.y;
                readMap->erase(entityID->id);
            }
        }
    })
    .whenDone([this](void){
        auto entityGenerator = ecs.getEntityGenerator("Entity");
        auto playerGenerator = ecs.getEntityGenerator("Player");

        auto &readMap = synchronizer.getDoubleMap().getReadMap();
        auto it = readMap->begin();
        while (it != readMap->end()) {
            size_t id = it->first;
            PacketData &data = it->second;

            if (data.isAlive && data.moveChanged) {
                if (data.entityType == EntityType::PLAYER1
                || data.entityType == EntityType::PLAYER2
                || data.entityType == EntityType::PLAYER3
                || data.entityType == EntityType::PLAYER4
                ) {
                    playerGenerator.instanciate(1,
                    Position{data.x, data.y},
                    EntityID{id},
                    animationManager.getAnimation(data.entityType),
                    Drawable{true, spriteManager.getSprite(data.entityType)});
                } else {
                    entityGenerator.instanciate(1,
                    Position{data.x, data.y},
                    EntityID{id},
                    animationManager.getAnimation(data.entityType),
                    Drawable{true, spriteManager.getSprite(data.entityType)});
                }
            }
            it++;
        }
        Synchronizer &synchronizer = this->getSynchronizer();
        synchronizer.getDoubleMap().closeRead();
    }).finish();

    ecs.newSystem<Animation, Drawable, EntityID>("AnimatePlayer")
        .withTags({ "PlayerControlled" })
        .each([this](float delta, EntityIterator<Animation, Drawable, EntityID> &entity){
                while (entity.hasNext()) {
                    entity.next();

                    Animation *animation = entity.getComponent<Animation>(0);
                    Drawable *drawable = entity.getComponent<Drawable>(1);
                    EntityID *entityID = entity.getComponent<EntityID>(2);

                    if (entityID->id == this->getGameMenu()->getPlayerID()) {
                        animation->currentImage.y = row;
                        animation->totalTime += delta;
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
                    }

                    animation->uvRect.left = animation->currentImage.x * animation->uvRect.width;
                    animation->uvRect.top = animation->currentImage.y * animation->uvRect.height;

                    drawable->uvRect.left = animation->uvRect.left;
                    drawable->uvRect.top = animation->uvRect.top;
                    drawable->uvRect.width = animation->uvRect.width;
                    drawable->uvRect.height = animation->uvRect.height;
                }
            })
        .finish();

    ecs.newSystem<Animation, Drawable>("AnimateSimpleEntity")
        .withTags({ "Entity" })
        .each([](float delta, EntityIterator<Animation, Drawable> &entity){
            while (entity.hasNext()) {
                entity.next();

                Animation *animation = entity.getComponent<Animation>(0);
                Drawable *drawable = entity.getComponent<Drawable>(1);

                if (animation->totalTime >= animation->switchTime) {
                    animation->totalTime -= animation->switchTime;
                    if (animation->currentImage.x < animation->imageCount.x - 1)
                        animation->currentImage.x = 0;
                    else
                        animation->currentImage.x++;
                }
                animation->uvRect.left = animation->currentImage.x * animation->uvRect.width;
                animation->uvRect.top = animation->currentImage.y * animation->uvRect.height;

                drawable->uvRect.left = animation->uvRect.left;
                drawable->uvRect.top = animation->uvRect.top;
                drawable->uvRect.width = animation->uvRect.width;
                drawable->uvRect.height = animation->uvRect.height;
            }
        })
        .finish();

    ecs.newSystem<Position, Drawable>("Draw")
        .withTags({ "Drawable" })
        .each([this](float delta, EntityIterator<Position, Drawable> &entity) {
            while (entity.hasNext()) {
                entity.next();

                Position *position = entity.getComponent<Position>(0);
                Drawable *drawable = entity.getComponent<Drawable>(1);

                if (position->x + drawable->uvRect.width <= 0 || position->x >= 1600
                    || position->y + drawable->uvRect.height <= 0 || position->y >= 800
                ) {
                    entity.remove();
                    continue;
                }

                drawable->sprite->setTextureRect(drawable->uvRect);
                drawable->sprite->setPosition(sf::Vector2f(position->x, position->y));
                this->getWindow().draw(*drawable->sprite);
            }
        })
        .finish();

    ecs.compile();
}

GameEntities::~GameEntities()
{
}

void GameEntities::update(bool *isDirectionMaintained, float deltaTime)
{
    for (int i = 0; i != 4; i++)
        this->isDirectionMaintained[i] = isDirectionMaintained[i];

    if (synchronizer.getDoubleQueue().isReadOpen()) {
        auto &vector = synchronizer.getDoubleQueue().getReadVector();

        auto entityGenerator = ecs.getEntityGenerator("Entity");
        auto playerGenerator = ecs.getEntityGenerator("Player");
        for (std::unique_ptr<IPacket> &packet : *vector) {
            if (packet->getPacketID() == SpawnPacket::PacketID()) {
                SpawnPacket *spawnpacket = dynamic_cast<SpawnPacket *>(packet.get());
                if (spawnpacket->isPlayer()) {
                    playerGenerator.instanciate(1,
                    Position{spawnpacket->getX(), spawnpacket->getY()},
                    EntityID{spawnpacket->getEntityID()},
                    animationManager.getAnimation(spawnpacket->getEntityType()),
                    Drawable{true, spriteManager.getSprite(spawnpacket->getEntityType())});
                } else {
                    entityGenerator.instanciate(1,
                    Position{spawnpacket->getX(), spawnpacket->getY()},
                    EntityID{spawnpacket->getEntityID()},
                    animationManager.getAnimation(spawnpacket->getEntityType()),
                    Drawable{true, spriteManager.getSprite(spawnpacket->getEntityType())}
                    );
                }
            } else if (packet->getPacketID() == InstanciatePlayerPacket::PacketID()) {
                InstanciatePlayerPacket *ipacket = dynamic_cast<InstanciatePlayerPacket *>(packet.get());
                gameMenu->setPlayerID(ipacket->getEntityID());
            }
        }
    }

    synchronizer.getDoubleQueue().closeRead();

    ecs.update(deltaTime);
}