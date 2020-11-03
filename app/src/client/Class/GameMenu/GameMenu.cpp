/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** GameMenu
*/

#include "client/Class/GameMenu/GameMenu.hpp"

GameMenu::GameMenu(): scene(LOGIN),
client(std::make_unique<TCPClient>()),
loadedTextures("./app/assets/Menu/"),
window(std::make_unique<sf::RenderWindow>(
    sf::VideoMode(1600, 800),
    "R-Type Menu",
    sf::Style::Close | sf::Style::Titlebar)
),
displayThread(std::make_unique<std::thread>(&GameMenu::handleDisplay, this))
{
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

    window->clear(sf::Color::White);
    for (size_t i = 0; i < sprites.size(); i++) {
        window->draw(*sprites[i]);
    }
    window->display();
}

bool GameMenu::isOpen()
{
    return (window->isOpen());
}

void GameMenu::handleEvents()
{
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }
}

void GameMenu::handleDisplay()
{
    while (isOpen()) {
        handleEvents();
        draw();
    }
}