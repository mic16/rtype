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
actualButton(menuButton::B_CREATE)
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
    const std::vector<std::unique_ptr<sf::Drawable>> &sprites = fixedDrawables.at(getScene());
    std::map<std::string, std::unique_ptr<sf::Drawable>> &spritesMod = modDrawables.at(getScene());

    window->clear(sf::Color::White);
    for (size_t i = 0; i < sprites.size(); i++)
        window->draw(*sprites[i]);
    for (std::map<std::string, std::unique_ptr<sf::Drawable>>::iterator it = spritesMod.begin(); it != spritesMod.end(); ++it) {
        if (modDrawables.at(scene).find(it->first) != modDrawables.at(scene).end())
            window->draw(*(getDrawable(getScene(), it->first)));
    }
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