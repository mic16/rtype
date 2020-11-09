/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameEntities
*/

#include "client/Class/GameEntities/GameEntities.hpp"
#include <boost/algorithm/string.hpp>

GameEntities::GameEntities()
{
    loadResources("app/assets/resources.txt");
}

void GameEntities::init()
{
    ecs.newEntityModel<Position, Velocity, Drawable>("Background")
        .addTags({"background", "drawable"})
        .finish();

    ecs.getEntityGenerator("Background")
        .instanciate(1, Position{0, 0}, Velocity{ -1, 0, 1}, resources[0]);
    
    ecs.newSystem<Position, Velocity, Drawable>("back_scroll")
        .withTags({ "background" })
        .each([](float delta, EntityIterator<Position, Velocity, Drawable> &entity) {
            while (entity.hasNext()) {
                Position* position = entity.getComponent<Position>(0);
                Velocity* velocity = entity.getComponent<Velocity>(1);
                Drawable* drawable = entity.getComponent<Drawable>(2);

                position->x += velocity->vx * velocity->speed;
                position->y += velocity->vy * velocity->speed;
                if (position->x == 1226)
                    position->x = 0;
                drawable->sprite->setPosition(position->x, position->y);
                entity.next();
            }
        }).finish();

                std::cout << "draw" << std::endl;
    ecs.newSystem<Position, Velocity, Drawable>("draw_back")
        .withTags({ "background" })
        .each([this](float delta, EntityIterator<Position, Velocity, Drawable> &entity) {
            while (entity.hasNext()) {
                Drawable* drawable = entity.getComponent<Drawable>(2);
                
                if (drawable->visible == true)
                    this->getWindow()->draw(*drawable->sprite);
                
                entity.next();
            }
    }).finish();

    ecs.newSystem<Position, Velocity, Drawable>("draw_front")
        .withoutTags( { "background" })
        .each([this](float delta, EntityIterator<Position, Velocity, Drawable> &entity) {
            while (entity.hasNext()) {
                Drawable* drawable = entity.getComponent<Drawable>(2);
                
                if (drawable->visible == true)
                    this->getWindow()->draw(*drawable->sprite);
                
                entity.next();
            }
    }).finish();

    ecs.compile();
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
    std::vector<std::string> words;

    if (!file)
        return ;
    while (getline(file, line)) {
        boost::split(words, line, boost::is_any_of(" "));
        texture.loadFromFile(words[0]);
        sprite.setTexture(texture);

        if (words.size() >= 3)
            sprite.setScale(std::stoi(words[1]), std::stoi(words[2]));

        res.texture = std::make_shared<sf::Texture>(texture);
        res.sprite = std::make_shared<sf::Sprite>(*res.texture);
        resources.push_back(res);
        words.clear();
    }
}

void GameEntities::update()
{
    ecs.update(1.f);
}