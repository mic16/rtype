/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** ResourceLoader
*/

#ifndef RESOURCELOADER_HPP_
#define RESOURCELOADER_HPP_

#include "SFML/Graphics.hpp"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include <regex>
#include <string>
#include <iostream>
#include <map>

class ResourceLoader {
    public:
        ResourceLoader(const std::string &path);
        ~ResourceLoader();

        const sf::Texture &operator[](const std::string &resource);
    private:
        std::map<std::string, sf::Texture> resources;
};

#endif /* !RESOURCELOADER_HPP_ */