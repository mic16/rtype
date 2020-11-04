/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameEntities
*/

#include "client/Class/GameEntities/GameEntities.hpp"

GameEntities::GameEntities()
{
    loadResources("app/assets/resources.txt");

    ecs.newEntityModel<Position, Velocity, Drawable>("Background")
        .addTags({"background", "drawable"})
        .finish();

    ecs.getEntityGenerator("Background")
        .instanciate(1, Position{0, 0}, Velocity{ 1, 1, 1}, resources[0]);
    
    ecs.newSystem<Position, Velocity, Drawable>("back_scroll")
        .each([](float delta, EntityIterator<Position, Velocity, Drawable> &entity) {
            while (entity.hasNext()) {
                entity.next();
                Position* position = entity.getComponent<Position>(0);
                Velocity* velocity = entity.getComponent<Velocity>(1);
                Drawable* drawable = entity.getComponent<Drawable>(2);

                position->x += velocity->vx * velocity->speed;
                position->y += velocity->vy * velocity->speed;
                drawable->sprite->setPosition(position->x, position->y);

            }
        }).finish();
    
}

GameEntities::~GameEntities()
{
}

void GameEntities::loadResources(std::string filename)
{
    Drawable res;
    std::string line;
    std::ifstream file(filename);
    sf::Texture texture;
    sf::Sprite sprite;

    if (!file)
        return ;
    while (getline(file, line)) {
        texture.loadFromFile(line);
        sprite.setTexture(texture);

        res.texture = std::make_shared<sf::Texture>(texture);
        res.sprite = std::make_shared<sf::Sprite>(*res.texture);
        resources.push_back(res);
    }
}

void GameEntities::update()
{
    ecs.update(1.f);
}

void GameEntities::draw(std::shared_ptr<sf::RenderWindow> window)
{
    window->draw(*resources[0].sprite);
}