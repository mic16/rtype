/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Components
*/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

struct Position {
    double x;
    double y;
};

struct EntityID {
    size_t id;
};

struct Velocity {
    double dirX;
    double dirY;
    double speed;
};

struct EntityStats {
    int hp;
    int maxHP;
    int damage;
};

struct EntityInfo {
    bool isEnemy;
    bool isFiring;
};

struct Hitbox {
    double w;
    double h;
};

struct ProjectileInfo {
    int damage;
};
#endif /* !COMPONENTS_HPP_ */
