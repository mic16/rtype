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
    loadResources("app/assets/resources.txt");
}

void GameEntities::init()
{
    ecs.newEntityModel<Position, Animation, Drawable>("Player")
        .addTags({ "Friendly", "EntityLiving", "PlayerControlled", "AnimatedPlayer" })
        .finish();

    ecs.newEntityModel<Position, Velocity, Drawable>("Background")
        .addTags({"background", "drawable"})
        .finish();

    ecs.getEntityGenerator("Background")
        .instanciate(1, Position{0, 0}, Velocity{ -1, 0, 0.3}, resources[1]);

    ecs.newSystem<Position, Velocity, Drawable>("back_scroll")
        .withTags({ "background" })
        .each([](float delta, EntityIterator<Position, Velocity, Drawable> &entity) {
            while (entity.hasNext()) {
                Position* position = entity.getComponent<Position>(0);
                Velocity* velocity = entity.getComponent<Velocity>(1);
                Drawable* drawable = entity.getComponent<Drawable>(2);

                position->x += velocity->vx * velocity->speed * delta;
                position->y += velocity->vy * velocity->speed * delta;
                if (position->x <= -1226)
                    position->x = 0;
                drawable->sprite->setPosition(position->x, position->y);
                entity.next();
            }
        }).finish();

    ecs.newSystem<Position, Animation, Drawable>("Movement")
        .withTags({ "PlayerControlled" })
        .each([this](float delta, EntityIterator<Position, Animation, Drawable> &entity) {
                while (entity.hasNext()) {
                    entity.next();

                    Position* position = entity.getComponent<Position>(0);
                    Animation* animation = entity.getComponent<Animation>(1);
                    Drawable* drawable = entity.getComponent<Drawable>(2);

                    if (isDirectionMaintained[DIRECTION::UP])
                        position->y -= 100 * delta;
                    if (isDirectionMaintained[DIRECTION::DOWN])
                        position->y += 100 * delta;
                    if (isDirectionMaintained[DIRECTION::LEFT])
                        position->x -= 100 * delta;
                    if (isDirectionMaintained[DIRECTION::RIGHT]) {
                        position->x += 100 * delta;
                    }
                    
                    drawable->sprite->setPosition(position->x, position->y);
                }
            })
        .finish();

        ecs.newSystem<Animation, Drawable>("AnimatePlayer")
        .withTags({ "AnimatedPlayer" })
        .each([this](float delta, EntityIterator<Animation, Drawable> &entity){
                while (entity.hasNext()) {
                    entity.next();

                    Animation *animation = entity.getComponent<Animation>(0);
                    Drawable *drawable = entity.getComponent<Drawable>(1);

                    animation->currentImage.y = row;
                    animation->totalTime += deltaTime;
                    if (animation->totalTime >= animation->switchTime) {
                        animation->totalTime -= animation->switchTime;
                        if (isDirectionMaintained[DIRECTION::UP])
                            animation->currentImage.x++;
                        else if (isDirectionMaintained[DIRECTION::DOWN])
                            animation->currentImage.x--;
                        if (animation->currentImage.x >= animation->imageCount.x) {
                            animation->currentImage.x--;
                        } else if (animation->currentImage.x <= 0) {
                            animation->currentImage.x++;
                        }
                    }
                    animation->uvRect.left = animation->currentImage.x * animation->uvRect.width;
                    animation->uvRect.top = animation->currentImage.y * animation->uvRect.height;
                    drawable->sprite->setTextureRect(animation->uvRect);
                }
            })
        .finish();

        ecs.newSystem<Drawable>("Draw_background")
        .withTags({ "background" })
        .each([this](float delta, EntityIterator<Drawable> &entity) {
            while (entity.hasNext()) {
                entity.next();

                Drawable *drawable = entity.getComponent<Drawable>(0);
                this->window.draw(*drawable->sprite);
            }
        })
        .finish();

        ecs.newSystem<Drawable>("Draw")
        .withTags({ "Friendly" })
        .withoutTags({"background"})
        .each([this](float delta, EntityIterator<Drawable> &entity) {
            while (entity.hasNext()) {
                entity.next();

                Drawable *drawable = entity.getComponent<Drawable>(0);
                this->window.draw(*drawable->sprite);
            }
        })
        .finish();

    ecs.compile();

    auto playerGenerator = ecs.getEntityGenerator("Player");
    playerGenerator.reserve(1);
    playerGenerator
        .instanciate(1, Position{ 200, 200 },
        Animation{sf::Vector2u(5, 5), sf::Vector2i(2, 0), 0, 0.05f,
        sf::IntRect(0, 0, resources[0].sprite->getTexture()->getSize().x / 5.0f, resources[0].sprite->getTexture()->getSize().y / 5.0f),
        false}, resources[0]);
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

        // if (words.size() >= 3)
            sprite.setScale(std::stoi(words[1]), std::stoi(words[2]));

        res.texture = std::make_shared<sf::Texture>(texture);
        res.sprite = std::make_shared<sf::Sprite>(*res.texture);
        resources.push_back(res);
        words.clear();
    }
}

void GameEntities::update(bool *isDirectionMaintained, float deltaTime)
{
    std::cout << this->deltaTime << std::endl;
    for (int i = 0; i != 4; i++)
        this->isDirectionMaintained[i] = isDirectionMaintained[i];
    this->deltaTime = deltaTime;
    ecs.update(deltaTime);
}