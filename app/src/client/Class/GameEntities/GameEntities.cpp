/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameEntities
*/

#include "client/Class/GameEntities/GameEntities.hpp"
#include "shared/Packet/SpawnPacket.hpp"
#include <boost/algorithm/string.hpp>

GameEntities::GameEntities(sf::RenderWindow &window, Synchronizer &synchronizer, EntitySpriteManager &spriteManager) : window(window), synchronizer(synchronizer), spriteManager(spriteManager)
{
    for (int i = 0; i != 4 ; i++)
        isDirectionMaintained[i] = false;
}

void GameEntities::init()
{

    ecs.newEntityModel<Position, Animation, EntityID, Drawable>("Player")
        .addTags({ "PlayerControlled", "Drawable" })
        .finish();
    
    ecs.newEntityModel<Position, EntityID, Drawable>("Enemy")
    .addTags({"Enemy"})
    .finish();

    ecs.newSystem<Position, EntityID>("UpdateEntities")
    .each([this](float delta, EntityIterator<Position, EntityID> &entity) {
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
                    continue;
                }

                position->x = data.x;
                position->y = data.y;
            }
        }

        synchronizer.getDoubleMap().closeRead();

    }).finish();

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

void GameEntities::createPlayer(int nbOfPlayers, sf::Vector2f position, sf::Vector2u totalFrames, sf::Vector2u startingFrame,
    float timeToSwitchFrames, sf::Vector2u textureSize, bool reverse, sf::Sprite *sprite, size_t id)
{
    auto playerGenerator = ecs.getEntityGenerator("Player");
    playerGenerator.reserve(nbOfPlayers);
    playerGenerator
        .instanciate(nbOfPlayers, Position{ position.x, position.y },
        Animation{ totalFrames, startingFrame, startingFrame, 0, timeToSwitchFrames,
        sf::IntRect(0, 0, textureSize.x / totalFrames.x, textureSize.y / totalFrames.y),
        reverse }, Drawable{ true, sprite }, EntityID { id });
}

void GameEntities::createBackground(sf::Sprite *sprite)
{
    sprite->setScale(4, 4);
    ecs.getEntityGenerator("Background")
        .instanciate(1, Position{0, 0}, Velocity{ -1, 0, 50}, Drawable{true, sprite});
}

void GameEntities::update(bool *isDirectionMaintained, float deltaTime)
{
    for (int i = 0; i != 4; i++)
        this->isDirectionMaintained[i] = isDirectionMaintained[i];
    this->deltaTime = deltaTime;

    auto &vector = synchronizer.getDoubleQueue().getReadVector();

    auto enemyGenerator = ecs.getEntityGenerator("Enemy");
    for (std::unique_ptr<IPacket> &packet : *vector) {
        if (packet->getPacketID() == SpawnPacket::PacketID()) {
            SpawnPacket *spawnpacket = dynamic_cast<SpawnPacket *>(packet.get());

            enemyGenerator.instanciate(1,
            Position{spawnpacket->getX(), spawnpacket->getY()},
            EntityID{spawnpacket->getEntityID()},
            Drawable{true, spriteManager.getSprite(spawnpacket->getEntityType())});
        }
    }

    synchronizer.getDoubleQueue().closeRead();

    ecs.update(deltaTime);
}