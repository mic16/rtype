/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameWindow
*/

#include "client/Class/GameWindow/GameWindow.hpp"

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

struct Animation {
    sf::Vector2u imageCount;
    sf::Vector2i currentImage;
    float totalTime = 0;
    float switchTime;
    sf::IntRect uvRect;
    bool reverse = false;
};

struct Display {
    std::shared_ptr<sf::RectangleShape> playerShape;
    std::shared_ptr<Animation> animation;
};

struct Draw {
    
};

GameWindow::GameWindow()
{
    gameWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "SFML window", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    // player = std::make_shared<Player>();
    for (int i = 0; i != 4 ; i++)
        isDirectionMaintained[i] = false;
    openWindow();
}

GameWindow::~GameWindow()
{
}

void GameWindow::openWindow()
{
    ECS ecs;
    int row = 0;
    float deltaTime = 0.0f;
    bool up;
    bool down;

    ecs.newEntityModel<Position, Status, /*Velocity,*/ Display>("Player")
        .addTags({ "Friendly", "EntityLiving", "PlayerControlled", "AnimatedPlayer" })
        .finish();

    ecs.newSystem<>("AnimatePlayer")
        .withTags({ "AnimatedPlayer" })
        .each([](float delta, EntityIterator<> &entity){
                while (entity.hasNext()) {
                    entity.next();

                    
                }
            })
        .finish();

    ecs.newSystem<Animation, Display>("AnimatePlayer")
        .withTags({ "AnimatedPlayer" })
        .each([&row, &deltaTime, &up, &down](float delta, EntityIterator<Animation, Display> &entity){
                while (entity.hasNext()) {
                    entity.next();

                    Animation *animation = entity.getComponent<Animation>(0);
                    Display *display = entity.getComponent<Display>(1);

                    animation->currentImage.y = row;
                    animation->totalTime += deltaTime;
                    if (animation->totalTime >= animation->switchTime) {
                        animation->totalTime -= animation->switchTime;
                        if (up)
                            animation->currentImage.x++;
                        else if (down)
                            animation->currentImage.x--;
                        if (animation->currentImage.x >= animation->imageCount.x) {
                            animation->currentImage.x--;
                        } else if (animation->currentImage.x <= 0) {
                            animation->currentImage.x++;
                        }
                    }
                    animation->uvRect.left = animation->currentImage.x * animation->uvRect.width;
                    animation->uvRect.top = animation->currentImage.y * animation->uvRect.height;
                    display->playerShape->setTextureRect(animation->uvRect);
                }
            })
        .finish();
    
    ecs.newSystem<Position /*, Velocity*/>("Movement")
        .withTags({ "PlayerControlled" })
        .each([this](float delta, EntityIterator<Position /*, Velocity*/> &entity) {
                while (entity.hasNext()) {
                    entity.next();

                    Position* position = entity.getComponent<Position>(0);
                    // Velocity* velocity = entity.getComponent<Velocity>(1);

                    if (isDirectionMaintained[DIRECTION::UP])
                        position->y -= 0.1;
                    if (isDirectionMaintained[DIRECTION::DOWN])
                        position->y += 0.1;
                    if (isDirectionMaintained[DIRECTION::LEFT])
                        position->x -= 0.1;
                    if (isDirectionMaintained[DIRECTION::RIGHT])
                        position->x += 0.1;

                    // position->x += velocity->dirX * velocity->speed;
                    // position->y += velocity->dirY * velocity->speed;

                    std::cout << entity.getName() << std::endl;
                }
            })
        .finish();

        // ecs.newSystem<Position>("Collision")
        //     .withTags({ "Projectile" })
        //     .each([&ecs](float delta, EntityIterator<Position>& entity) {
        //             auto players = ecs.lookup<Position, Hitbox>("Player");

        //             while (entity.hasNext()) {
        //                 entity.next();

        //                 Position* projectilePosition = entity.getComponent<Position>(0);

        //                 players.reset();
        //                 while (players.hasNext()) {
        //                     players.next();

        //                     Position* playerPosition = players.getComponent<Position>(0);
        //                     Hitbox* playerHitbox = players.getComponent<Hitbox>(1);

        //                     if (true) {
        //                         std::cout << playerPosition->x << " " << playerPosition->y << std::endl;
        //                         players.remove();
        //                         entity.remove();
        //                         break;
        //                     }
        //                 }
        //             }
        //         })
        //     .finish();

    ecs.compile();

    auto playerGenerator = ecs.getEntityGenerator("Player");
    playerGenerator.reserve(1);
    // for (int i = 0; i < 4; i++) {
    playerGenerator
        .instanciate(1, Position{ 200, 200 }, /*Velocity{ 1, 1, 1 }*/ Display{ initPlayer(), std::make_shared<Animation>(sf::Vector2u(5, 5), sf::Vector2i(2, 0), 0, 0.05f, sf::IntRect(0, 0, playerTexture->getSize().x / static_cast<float>(5), playerTexture->getSize().y / static_cast<float>(5)), false)});
    // }

    // sf::Vector2u imageCount;
    // sf::Vector2i currentImage;
    // float totalTime = 0;
    // float switchTime;
    // sf::IntRect uvRect;
    // bool reverse = false;

    sf::Clock clock;

    while (gameWindow->isOpen()) {
        deltaTime = clock.restart().asSeconds();

        while (gameWindow->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                gameWindow->close();
            if (event.type == sf::Event::KeyPressed)
                checkKeyPressed(event.key.code);
            if (event.type == sf::Event::KeyReleased)
                checkKeyReleased(event.key.code);
                    
        }
        
        // updatePlayerPosition();
        up = isDirectionMaintained[DIRECTION::UP];
        down = isDirectionMaintained[DIRECTION::DOWN];

        ecs.update(1.f);

        // player->getPlayerAnimation()->update(0, deltaTime, isDirectionMaintained[DIRECTION::UP], isDirectionMaintained[DIRECTION::DOWN]);
        // player->getPlayerShape()->setTextureRect(player->getPlayerAnimation()->getUvRect());
        draw();
    }
}

std::shared_ptr<sf::RectangleShape> GameWindow::initPlayer()
{
    playerShape = std::make_shared<sf::RectangleShape>(sf::Vector2f(50, 50));
    playerShape.get()->setPosition(200, 200);
    playerTexture = std::make_shared<sf::Texture>();
    playerTexture.get()->loadFromFile("app/assets/sprites/r-typesheet42.png");
    playerShape.get()->setTexture(playerTexture.get());
    return (playerShape);
}

void GameWindow::updatePlayerPosition()
{
    // if (isDirectionMaintained[DIRECTION::UP])
    //     player.get()->setPosition(0, -0.1);
    // if (isDirectionMaintained[DIRECTION::DOWN])
    //     player.get()->setPosition(0, 0.1);
    // if (isDirectionMaintained[DIRECTION::LEFT])
    //     player.get()->setPosition(-0.1, 0);
    // if (isDirectionMaintained[DIRECTION::RIGHT])
    //     player.get()->setPosition(0.1, 0);
}

void GameWindow::checkKeyReleased(sf::Keyboard::Key key)
{
    switch (key) {
        case (sf::Keyboard::Z):
            isDirectionMaintained[DIRECTION::UP] = false;
            break;
        case (sf::Keyboard::Q):
            isDirectionMaintained[DIRECTION::LEFT] = false;
            break;
        case (sf::Keyboard::S):
            isDirectionMaintained[DIRECTION::DOWN] = false;
            break;
        case (sf::Keyboard::D):
            isDirectionMaintained[DIRECTION::RIGHT] = false;
            break;
        default:
            break;
    }
}

void GameWindow::checkKeyPressed(sf::Keyboard::Key key)
{
    switch (key) {
        case (sf::Keyboard::Z):
            isDirectionMaintained[DIRECTION::UP] = true;
            break;
        case (sf::Keyboard::Q):
            isDirectionMaintained[DIRECTION::LEFT] = true;
            break;
        case (sf::Keyboard::S):
            isDirectionMaintained[DIRECTION::DOWN] = true;
            break;
        case (sf::Keyboard::D):
            isDirectionMaintained[DIRECTION::RIGHT] = true;
            break;
        default:
            break;
    }
}

void GameWindow::draw()
{
    gameWindow.get()->clear(sf::Color(150, 150, 150));
    gameWindow.get()->draw(player->getPlayerShape()[0]);
    gameWindow.get()->display();
}