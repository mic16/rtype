/*
** EPITECH PROJECT, 2020
** ECS [WSL: Ubuntu]
** File description:
** main
*/

#include "ECS.hpp"
#include <iostream>

struct Position {
    int x;
    int y;
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

struct Velocity {
    float dirX;
    float dirY;
    float speed;
};

struct Hitbox {
    size_t x;
    size_t y;
    size_t w;
    size_t h;
};


int main(int ac, char** av) {
    try {
        ECS ecs;

        ecs.newEntityModel<Position, Status, Velocity>("Player")
            .addTags({ "Friendly", "EntityLiving" })
            .finish();

        ecs.newEntityModel<Position, Status, Velocity>("Enemy")
            .addTags({ "Hostile", "EntityLiving" })
            .finish();

        ecs.newEntityModel<Position, ProjectileStats, Velocity>("Projectile")
            .addTags({"Hostile", "Projectile"})
            .finish();

        ecs.newSystem<Position, Velocity>("Movement")
            .withTags({  "Hostile" })
            .withoutTags({"Projectile"})
            .each([](float delta, EntityIterator<Position, Velocity> &entity) {
                    while (entity.hasNext()) {
                        entity.next();

                        Position* position = entity.getComponent<Position>(0);
                        Velocity* velocity = entity.getComponent<Velocity>(1);

                        position->x += velocity->dirX * velocity->speed;
                        position->y += velocity->dirY * velocity->speed;

                        std::cout << entity.getName() << std::endl;

                        if (position->x > 100) {
                            entity.remove();
                        }
                    }
                })
            .finish();

                ecs.newSystem<Position>("Collision")
                    .withTags({ "Projectile" })
                    .each([&ecs](float delta, EntityIterator<Position>& entity) {
                            auto players = ecs.lookup<Position, Hitbox>("Player");

                            while (entity.hasNext()) {
                                entity.next();

                                Position* projectilePosition = entity.getComponent<Position>(0);

                                players.reset();
                                while (players.hasNext()) {
                                    players.next();

                                    Position* playerPosition = players.getComponent<Position>(0);
                                    Hitbox* playerHitbox = players.getComponent<Hitbox>(1);

                                    if (true) {
                                        std::cout << playerPosition->x << " " << playerPosition->y << std::endl;
                                        players.remove();
                                        entity.remove();
                                        break;
                                    }
                                }
                            }
                        })
                    .finish();

            ecs.compile();

            auto playerGenerator = ecs.getEntityGenerator("Player");
            playerGenerator.reserve(1000);
            for (int i = 0; i < 1000; i++) {
                playerGenerator
                    .instanciate(1, Position{ rand(), rand() }, Velocity{ 1, 1, 1 });
            }
            
            ecs.getEntityGenerator("Projectile")
                .instanciate(4, Position{ 0,0 }, Velocity{ 1, 1, 1 });

            ecs.getEntityGenerator("Enemy")
                .instanciate(4, Position{ 0,0 }, Velocity{ 1, 1, 1 });


            
                ecs.update(1.f);
            
    } catch (const char* e) {
        std::cout << e << std::endl;
    }
    return 0;
}