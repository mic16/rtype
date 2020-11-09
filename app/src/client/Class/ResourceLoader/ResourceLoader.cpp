/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** ResourceLoader
*/

#include "client/Class/ResourceLoader/ResourceLoader.hpp"

ResourceLoader::ResourceLoader(const std::string &path)
{
    if (boost::filesystem::is_directory(path)) {
        std::regex fileReg("^\".*\\/(.+)(\\.jpeg|\\.jpg|\\.png)\"$");
        for(boost::filesystem::directory_entry &entry : boost::make_iterator_range(boost::filesystem::directory_iterator(path), {})) {
            std::ostringstream sstream;
            std::smatch file_match;
            sstream << entry;
            std::string fileStr = sstream.str();
            std::cout << fileStr << " found." << std::endl;
            if (std::regex_search(fileStr, file_match, fileReg)) {
                std::cout << fileStr << " is loading." << std::endl;
                std::string filename = file_match[1];
                resources.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>(filename, std::make_shared<sf::Texture>()));
                boost::erase_all(fileStr, "\"");
                if (resources.at(filename)->loadFromFile(fileStr)) {
                    std::cout << fileStr << " is loaded." << std::endl;
                } else {
                    std::cout << fileStr << " cannot be loaded." << std::endl;
                }
            } else {
                std::cout << fileStr << " cannot be loaded." << std::endl;
            }
        }
    } else {
        std::cout << "Cannot find directory " << path << std::endl;
    }
}

ResourceLoader::~ResourceLoader()
{
}

std::shared_ptr<sf::Texture> &ResourceLoader::operator[](const std::string &resource)
{
    return (resources.at(resource));
}