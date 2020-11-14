/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Game
*/

#include "server/Class/GameServer/Game.hpp"
#include "server/Class/MessageHandlers/ServerSpawnMessageHandler.hpp"
#include "server/Class/MessageHandlers/ServerDeathMessageHandler.hpp"
#include "server/Class/MessageHandlers/ServerPingMessageHandler.hpp"
#include "server/Class/MessageHandlers/ServerDamageMessageHandler.hpp"
#include "server/Class/MessageHandlers/ServerFireMessageHandler.hpp"
#include "server/Class/MessageHandlers/ServerMoveMessageHandler.hpp"
#include "server/Class/MessageHandlers/ServerPositionMessageHandler.hpp"
#include "server/Class/MessageHandlers/ServerInstanciatePlayerMessageHandler.hpp"

#include "shared/Packet/PlayerEnterRoomPacket.hpp"

Game::Game():
    Synchronizer(),
    lobby(Ladder::genId()),
    gameServer(*this, networkHandler)
{
    networkHandler.registerMessageHandler(new ServerSpawnMessageHandler(*this));
    networkHandler.registerMessageHandler(new ServerDeathMessageHandler(*this));
    networkHandler.registerMessageHandler(new ServerPingMessageHandler(*this));
    networkHandler.registerMessageHandler(new ServerDamageMessageHandler(*this));
    networkHandler.registerMessageHandler(new ServerFireMessageHandler(*this));
    networkHandler.registerMessageHandler(new ServerMoveMessageHandler(*this));
    networkHandler.registerMessageHandler(new ServerPositionMessageHandler(*this));
    networkHandler.registerMessageHandler(new ServerInstanciatePlayerMessageHandler(*this));
}

Game::~Game()
{
}

void Game::init() {
    ecs.newEntityModel<Position, Velocity, EntityID, Hitbox, EntityInfo, EntityStats>("Player")
    .addTags({"Player", "Friendly", "Damageable"})
    .finish();

    ecs.newEntityModel<Position, Velocity, EntityID, Hitbox, EntityInfo, ProjectileInfo>("Projectile")
    .addTags({"DamageOnTouch", "Projectile"})
    .finish();

    ecs.newEntityModel<Position, Velocity, EntityID, Hitbox, EntityInfo, EntityStats>("Enemy")
    .addTags({"Enemy", "DamageOnTouch", "Damageable"})
    .finish();

    ecs.newEntityModel<Position, Velocity, EntityID, Hitbox>("Wall")
    .finish();

    ecs.newEntityModel<Position, Velocity, EntityID, Hitbox, EntityInfo, EntityStats>("DestructibleWall")
    .addTags({"DamageOnTouch", "Damageable"})
    .finish();

    ecs.newSystem<Velocity, EntityID, EntityInfo>("UpdateEntities")
    .withTags({"Player"})
    .each([this](float delta, EntityIterator<Velocity, EntityID, EntityInfo> &entity) {
        if (this->getDoubleMap().isReadClose())
            return;

        auto &readMap = this->getDoubleMap().getReadMap();
        while (entity.hasNext()) {
            entity.next();

            Velocity *velocity = entity.getComponent<Velocity>(0);
            EntityID *entityID = entity.getComponent<EntityID>(1);
            EntityInfo *entityInfo = entity.getComponent<EntityInfo>(2);

            if (readMap->find(entityID->id) != readMap->end()) {
                PacketData &data = readMap->at(entityID->id);
                if (data.moveChanged) {
                    velocity->dirX = data.dirX;
                    velocity->dirY = data.dirY;
                }

                if (data.fireChanged) {
                    entityInfo->isFiring = data.isFiring;
                }
            }
        }
    })
    .whenDone([this](void){
        this->getDoubleMap().closeRead();
    })
    .finish();

    ecs.newSystem<EntityID>("SpawnEnemy")
    .withTags({"Enemy"})
    .each([this](float delta, EntityIterator<EntityID> &entity) {
        auto enemyGenerator = this->getECS().getEntityGenerator("Enemy");
        if (entity.getSize() == 0) {
            size_t spawnType = rand() % 1;
            if (spawnType == 0) {

                for (int i = 0; i < 5; i++) {
                    double x = this->getMapWidth();
                    double y = this->getMapHeight()/5.0*i;
                    size_t id = this->getNextEntityID();

                    enemyGenerator.instanciate(1,
                        Position{x, y},
                        Velocity{-1, 0, 400},
                        EntityID{id},
                        Enemy1Hitbox,
                        EntityInfo{true, true, EntityType::ENEMY1},
                        EntityStats{100, 100, 20, 0}
                    );
                    this->getNetworkHandler().broadcast(SpawnPacket(id, EntityType::ENEMY1, x, y, 0));
                }
            }
        }
    }).finish();

    size_t hashEnemy = ecs.getHash("Enemy");
    ecs.newSystem<Position, EntityID, EntityInfo, Hitbox, EntityStats>("SpawnProjectile")
    .withoutTags({"Projectile"})
    .each([this, hashEnemy](float delta, EntityIterator<Position, EntityID, EntityInfo, Hitbox, EntityStats> &entity) {
        static Hitbox projectile = ProjectileHitbox;
        auto projectileGenerator = this->getECS().getEntityGenerator("Projectile");
        while (entity.hasNext()) {
            entity.next();

            Position *position = entity.getComponent<Position>(0);
            EntityID *entityID = entity.getComponent<EntityID>(1);
            EntityInfo *entityInfo = entity.getComponent<EntityInfo>(2);
            Hitbox *hitbox = entity.getComponent<Hitbox>(3);
            EntityStats *entityStats = entity.getComponent<EntityStats>(4);

            if (entityInfo->isFiring) {
                entityStats->fireTimer += delta;
                if ((entity.getEntityType() != hashEnemy && entityStats->fireTimer > 0.1) || entityStats->fireTimer > 0.5) {
                    bool isEnemy = entityInfo->isEnemy;
                    size_t id = this->getNextEntityID();
                    double x = isEnemy?position->x-projectile.w:position->x + hitbox->w;
                    double y = position->y + hitbox->h / 2;

                    projectileGenerator.instanciate(1,
                        Position{x, y},
                        Velocity{isEnemy?-1.0:1.0, 0, 1000},
                        EntityID{id},
                        ProjectileHitbox,
                        EntityInfo{isEnemy, false, EntityType::PROJECTILE1},
                        ProjectileInfo{entityStats->damage}
                    );

                    this->getNetworkHandler().broadcast(SpawnPacket(id, EntityType::PROJECTILE1, x, y, 0));
                    entityStats->fireTimer = 0;
                }
            }
        }
    }).finish();

    size_t hashProjectile = ecs.getHash("Projectile");
    ecs.newSystem<Position, Velocity, EntityID, EntityInfo, Hitbox>("MoveEntity")
    .each([this, hashProjectile](float delta, EntityIterator<Position, Velocity, EntityID, EntityInfo, Hitbox> &entity) {
        while (entity.hasNext()) {
            entity.next();

            Position *position = entity.getComponent<Position>(0);
            Velocity *velocity = entity.getComponent<Velocity>(1);
            EntityID *entityID = entity.getComponent<EntityID>(2);
            EntityInfo *entityInfo = entity.getComponent<EntityInfo>(3);
            Hitbox *hitbox = entity.getComponent<Hitbox>(4);

            double moveX = velocity->dirX * velocity->speed * delta;
            double moveY = velocity->dirY * velocity->speed * delta;

            if (entityInfo->isEnemy) {
                if (position->x + hitbox->w + moveX < 0 || position->y + hitbox->h + moveY < 0 || position->y + moveY > this->getMapHeight()) {
                    this->getNetworkHandler().broadcast(DeathPacket(entityID->id));
                    entity.remove();
                    continue;
                }
            } else {
                    if (entity.getEntityType() == hashProjectile) {
                        if (position->x + hitbox->w  <= -50 || position->x >= this->getMapWidth() + 50 ||
                            position->y + hitbox->h  <= 0 || position->y >= this->getMapHeight()) {
                            this->getNetworkHandler().broadcast(DeathPacket(entityID->id));
                            entity.remove();
                            continue;
                        }
                    } else {
                        if (position->x + moveX < 0 || position->x + hitbox->w + moveX > this->getMapWidth() ||
                            position->y + moveY < 0 || position->y + hitbox->h + moveY > this->getMapHeight()) {
                            continue;
                        }
                    }
            }

            if (moveX != 0 || moveY != 0) {
                position->x += moveX;
                position->y += moveY;
                this->getNetworkHandler().broadcast(PositionPacket(entityID->id, position->x, position->y, entityInfo->entityType));
            }
        }
    }).finish();

    ecs.newSystem<Position, Hitbox, EntityInfo, EntityID, EntityStats>("ApplyDamage")
    .withTags({"Damageable"})
    .each([this](float delta, EntityIterator<Position, Hitbox, EntityInfo, EntityID, EntityStats> &entity) {
        auto projectileIterator = this->getECS().lookup<Position, Hitbox, EntityInfo, EntityID, ProjectileInfo>("Projectile");
        while (entity.hasNext()) {
            entity.next();

            Position *entityPosition = entity.getComponent<Position>(0);
            Hitbox *entityHitbox = entity.getComponent<Hitbox>(1);
            EntityInfo *entityInfo = entity.getComponent<EntityInfo>(2);
            EntityID *entityID = entity.getComponent<EntityID>(3);
            EntityStats *entityStats = entity.getComponent<EntityStats>(4);

            projectileIterator.reset();
            while (projectileIterator.hasNext()) {
                projectileIterator.next();

                EntityInfo *projectileEntityInfo = projectileIterator.getComponent<EntityInfo>(2);
                if ((!entityInfo->isEnemy && projectileEntityInfo->isEnemy) ||
                    (entityInfo->isEnemy && !projectileEntityInfo->isEnemy))
                {
                    Position *projectilePosition = projectileIterator.getComponent<Position>(0);
                    Hitbox *projectileHitbox = projectileIterator.getComponent<Hitbox>(1);
                    EntityID *projectileID = projectileIterator.getComponent<EntityID>(3);
                    ProjectileInfo *projectileInfo = projectileIterator.getComponent<ProjectileInfo>(4);

                    if (entityPosition->x < projectilePosition->x + projectileHitbox->w &&
                        entityPosition->x + entityHitbox->w > projectilePosition->x &&
                        entityPosition->y < projectilePosition->y + projectileHitbox->h &&
                        entityPosition->y + entityHitbox->h > projectilePosition->y)
                    {
                        entityStats->hp -= projectileInfo->damage;
                        this->getNetworkHandler().broadcast(DamagePacket(entityID->id, projectileInfo->damage, entityStats->hp, entityStats->maxHP));
                        this->getNetworkHandler().broadcast(DeathPacket(projectileID->id)); // Kill projectile
                        projectileIterator.remove();

                        if (entityStats->hp <= 0) {
                            this->getNetworkHandler().broadcast(DeathPacket(entityID->id)); // Kill Entity
                            entity.remove();
                            break;
                        }
                    }
                }

            }
        }
    }).finish();
}

void Game::loadExtensions(std::vector<std::unique_ptr<IExtension>> &extensions) {

}

void Game::compile() {
    ecs.compile();
}

void Game::update() {
    auto now = std::chrono::high_resolution_clock::now();
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastTime);
    double delta = nanos.count() / 1000000000.0;

    lastTime = now;
    ecs.update(delta);
}

const server_info_t Game::setGameServer()
{
    server_info_t info;

    gameServer.configure();
    info.address = "127.0.0.1";
    info.port = gameServer.getPort();
    return (info);
}

void Game::startGame()
{
    static unsigned short playerID = 1;
    bool canLogin = true;
    gameServer.run();
    lastTime = std::chrono::high_resolution_clock::now();
    init();
    compile();
    auto t1 = std::chrono::high_resolution_clock::now();
    networkHandler.getLastTRequestStatus() = std::chrono::high_resolution_clock::now();
    while (true) {
        if (canLogin && getDoubleQueue().isReadOpen()) {
            auto &vector = getDoubleQueue().getReadVector();
            for (std::unique_ptr<IPacket> &packet : *vector) {
                if (packet->getPacketID() == PlayerEnterRoomPacket::PacketID()) {
                    PlayerEnterRoomPacket *PERPacket = dynamic_cast<PlayerEnterRoomPacket *>(packet.get());

                    auto playerGenerator = ecs.getEntityGenerator("Player");
                    double x = 0;
                    double y = getMapHeight() / 2;
                    size_t id = getNextEntityID();
                    size_t type = 0;


                    playerGenerator.instanciate(1,
                    Position{x, y},
                    Velocity{0, 0, 400},
                    EntityID{id},
                    PlayerHitbox,
                    EntityInfo{false, false, EntityType::PLAYER1},
                    EntityStats{100, 100, 20});

                    networkHandler.broadcast(SpawnPacket(id, EntityType::PLAYER1, x, y, playerID));
                    networkHandler.send(*PERPacket->getNetworkClient(), InstanciatePlayerPacket(id));
                    playerID += 1;
                }
            }
            getDoubleQueue().closeRead();
        }
        update();
        auto t2 = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::duration<double>>(t2 - networkHandler.getLastTRequestStatus()).count() > 0.1) {
            networkHandler.broadcast(PingPacket());
            networkHandler.getLastTRequestStatus() = std::chrono::high_resolution_clock::now();
        }
        if (std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count() > 10) {
            networkHandler.checkClientsConnection();
            t1 = std::chrono::high_resolution_clock::now();
            if (canLogin) canLogin = false;
        }
    }
    gameServer.join();
}

Ladder &Game::getLobby()
{
    return (lobby);
}

ECS &Game::getECS() {
    return ecs;
}

NetworkHandler &Game::getNetworkHandler() {
    return networkHandler;
}

size_t Game::getNextEntityID() {
    return entityId++;
}
