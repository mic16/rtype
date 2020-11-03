/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** EConnection
*/

#ifndef ECONNECTION_HPP_
#define ECONNECTION_HPP_

#include <exception>
#include <string>

class EConnection : public std::exception {
    public:
        EConnection(const std::string &err): std::exception(), errdef(err) {}

        const char* what() const noexcept override { return errdef.c_str(); }
    private:
        const std::string errdef;
};

#endif /* !ECONNECTION_HPP_ */
