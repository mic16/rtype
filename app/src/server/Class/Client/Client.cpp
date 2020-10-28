/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** Client
*/

#include "server/Class/Client/Client.hpp"

Client::Client(boost::asio::io_service &service): m_socket(service)
{
}

Client::~Client()
{
}

bool Client::setClient()
{
    if (!m_socket.is_open()) return (false);
    m_address = m_socket.remote_endpoint().address().to_string();
    m_port = m_socket.remote_endpoint().port();

    return (true);
}

const std::string &Client::getAddress() const
{ return (m_address); }

const unsigned int Client::getPort() const
{ return (m_port); }