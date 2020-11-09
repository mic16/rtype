/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** EFinished
*/

#ifndef EFINISHED_HPP_
#define EFINISHED_HPP_

#include <exception>
#include <string>

class EFinished : public std::exception {
    public:
        EFinished(const std::string &err): std::exception(), errdef(err) {}

        const char* what() const noexcept override { return errdef.c_str(); }
    private:
        const std::string errdef;
};

#endif /* !EFINISHED_HPP_ */
