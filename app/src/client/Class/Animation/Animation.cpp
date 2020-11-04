/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Animation
*/

#include "client/Class/Animation/Animation.hpp"

Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    // totalTime = 0;
    currentImage.x = 2;

    uvRect.width = texture->getSize().x / static_cast<float>(imageCount.x);
    uvRect.height = texture->getSize().y / static_cast<float>(imageCount.y);
    // std::cout << "UvRect Height: " << uvRect.height << std::endl;
    std::cout << texture->getSize().x << " " << static_cast<float>(imageCount.x);
}

Animation::~Animation()
{
}

void Animation::update(int row, float deltaTime, bool up, bool down)
{
    currentImage.y = row;
    totalTime += deltaTime;
    if (totalTime >= switchTime) {
        // totalTime -= switchTime;
        // if (!reverse)
        //     currentImage.x++;
        // else
        //     currentImage.x--;
        // if (currentImage.x >= imageCount.x) {
        //     currentImage.x--;
        //     reverse = true;
        // } else if (currentImage.x <= 0) {
        //     reverse = false;
        // }
        totalTime -= switchTime;
        if (up)
            currentImage.x++;
        else if (down)
            currentImage.x--;
        if (currentImage.x >= imageCount.x) {
            currentImage.x--;
        } else if (currentImage.x <= 0) {
            currentImage.x++;
        }
    }
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}

sf::IntRect Animation::getUvRect()
{
    return (uvRect);
}