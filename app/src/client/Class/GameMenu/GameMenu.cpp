/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameMenu
*/

#include "client/Class/GameMenu/GameMenu.hpp"

GameMenu::GameMenu(): scene(LOGIN),
username("..."),
loadedTextures("./app/assets/Menu/"),
window(std::make_unique<sf::RenderWindow>(
    sf::VideoMode(1600, 800),
    "R-Type Menu",
    sf::Style::Close | sf::Style::Titlebar)
),
displayThread(std::make_unique<std::thread>(&GameMenu::handleDisplay, this)),
buffer(1024),
actualButton(0)
{
    client = std::make_unique<TCPClient>(this);
    initDrawables();
    window->setFramerateLimit(60);
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
    const std::vector<std::unique_ptr<sf::Drawable>> &sprites = fixedDrawables.at(scene);
    std::map<std::string, std::unique_ptr<sf::Drawable>> &spritesMod = modDrawables.at(scene);

    window->clear(sf::Color::White);
    for (size_t i = 0; i < sprites.size(); i++)
        window->draw(*sprites[i]);
    for (std::map<std::string, std::unique_ptr<sf::Drawable>>::iterator it = spritesMod.begin(); it != spritesMod.end(); ++it)
        window->draw(*(it->second));
    window->display();
}

bool GameMenu::isOpen()
{
    return (window->isOpen());
}

void GameMenu::handleDisplay()
{
    while (isOpen()) {
        handleEvents();
        draw();
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