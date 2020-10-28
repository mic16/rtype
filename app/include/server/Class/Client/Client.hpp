/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <boost/asio.hpp>
#include <string>

class Client {
    public:
        Client(boost::asio::io_service &service);
        ~Client();

        bool setClient(void);

        const std::string &getAddress() const;
        const unsigned int getPort() const;

        boost::asio::ip::tcp::socket m_socket;
    private:

        std::string m_address;
        unsigned int m_port;
        char *m_username = nullptr;
};

#endif /* !CLIENT_HPP_ */
