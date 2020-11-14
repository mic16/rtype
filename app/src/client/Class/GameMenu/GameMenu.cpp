/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameMenu
*/

#include "client/Class/GameMenu/GameMenu.hpp"

#include "client/Class/MessageHandlers/ClientSpawnMessageHandler.hpp"
#include "client/Class/MessageHandlers/ClientDeathMessageHandler.hpp"
#include "client/Class/MessageHandlers/ClientPingMessageHandler.hpp"
#include "client/Class/MessageHandlers/ClientDamageMessageHandler.hpp"
#include "client/Class/MessageHandlers/ClientFireMessageHandler.hpp"
#include "client/Class/MessageHandlers/ClientMoveMessageHandler.hpp"
#include "client/Class/MessageHandlers/ClientPositionMessageHandler.hpp"
#include "client/Class/MessageHandlers/ClientInstanciatePlayerMessageHandler.hpp"


GameMenu::GameMenu(): scene(LOGIN),
username("..."),
loadedTextures("./app/assets/Menu/"),
window(
    sf::VideoMode(1600, 800),
    "R-Type",
    sf::Style::Close | sf::Style::Titlebar
),
buffer(1024),
actualButton(menuButton::B_CREATE),
gameEntities(this, window, synchronizer, spriteManager, animationManager),
background(window, 250)
{
    client = std::make_unique<TCPClient>(this);
    initDrawables();
    gameEntities.init();
    playerId = 0;
    for (int i = 0; i != 4 ; i++)
        isDirectionMaintained[i] = false;
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    networkHandler.registerMessageHandler(new ClientSpawnMessageHandler(synchronizer));
    networkHandler.registerMessageHandler(new ClientDeathMessageHandler(synchronizer));
    networkHandler.registerMessageHandler(new ClientPingMessageHandler(synchronizer));
    networkHandler.registerMessageHandler(new ClientDamageMessageHandler(synchronizer));
    networkHandler.registerMessageHandler(new ClientFireMessageHandler(synchronizer));
    networkHandler.registerMessageHandler(new ClientMoveMessageHandler(synchronizer));
    networkHandler.registerMessageHandler(new ClientPositionMessageHandler(synchronizer));
    networkHandler.registerMessageHandler(new ClientInstanciatePlayerMessageHandler(synchronizer));

    displayThread = std::make_unique<std::thread>(&GameMenu::handleDisplay, this);
}

GameMenu::~GameMenu()
{
}

int GameMenu::run()
{
    try {
        client->connectTo(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 3000));
        client->run();
    } catch (std::exception &ec) {
        std::cout << ec.what() << std::endl;
        return (1);
    }
    displayThread->join();
    return (0);
}

void GameMenu::draw()
{
    const std::vector<std::unique_ptr<sf::Drawable>> &sprites = fixedDrawables.at(getScene());
    std::map<std::string, std::unique_ptr<sf::Drawable>> &spritesMod = modDrawables.at(getScene());

    window.clear(sf::Color::White);
    for (size_t i = 0; i < sprites.size(); i++)
        window.draw(*sprites[i]);
    for (std::map<std::string, std::unique_ptr<sf::Drawable>>::iterator it = spritesMod.begin(); it != spritesMod.end(); ++it) {
        if (modDrawables.at(scene).find(it->first) != modDrawables.at(scene).end())
            window.draw(*(getDrawable(getScene(), it->first)));
    }
    window.display();
}

void GameMenu::draw(float deltaTime)
{
    if (gameEntities.isGamePlaying()) {
            window.clear(sf::Color::White);
            background.update(deltaTime);
            background.draw();
            gameEntities.update(isDirectionMaintained, deltaTime);
            window.display();
    }
}

bool GameMenu::isOpen()
{
    return (window.isOpen());
}

void GameMenu::handleDisplay()
{
    float deltaTime = 0.0f;
    sf::Clock clock;

    while (isOpen()) {
        deltaTime = clock.restart().asSeconds();
        handleEvents();
        if (getScene() == sceneName::GAME) {
            draw(deltaTime);
        } else {
            draw();
        }
    }
}

const sceneName GameMenu::getScene()
{
    const std::lock_guard<std::mutex> lock(scene_mutex);
    return (scene);
}

void GameMenu::setScene(const sceneName sc_name)
{
    const std::lock_guard<std::mutex> lock(scene_mutex);
    scene = sc_name;
}

const std::unique_ptr<sf::Drawable> &GameMenu::getDrawable(sceneName scene, const std::string &key)
{
    const std::lock_guard<std::mutex> lock(drawables_mutex);
    return (modDrawables.at(scene)[key]);
}

void GameMenu::setDrawableTextStr(sceneName scene, const std::string &key, const std::string &text)
{
    const std::lock_guard<std::mutex> lock(drawables_mutex);
    dynamic_cast<sf::Text *>(modDrawables.at(scene)[key].get())->setString(text);
}

void GameMenu::setDrawableTextColor(sceneName scene, const std::string &key, const sf::Color &color)
{
    const std::lock_guard<std::mutex> lock(drawables_mutex);
    dynamic_cast<sf::Text *>(modDrawables.at(scene)[key].get())->setFillColor(color);
}

void GameMenu::setDrawableSpriteTexture(sceneName scene, const std::string &key, const std::string &texture)
{
    const std::lock_guard<std::mutex> lock(drawables_mutex);
    dynamic_cast<sf::Sprite *>(modDrawables.at(scene)[key].get())->setTexture(*loadedTextures[texture]);
}