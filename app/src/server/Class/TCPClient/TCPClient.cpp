/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** TCPClient
*/

#include "server/Class/TCPClient/TCPClient.hpp"

TCPClient::TCPClient(boost::asio::io_context &service): m_socket(service), buffer(1024)
{
    m_packet = new char[1024];
}

TCPClient::~TCPClient()
{
    if (m_packet) delete m_packet;
}

bool TCPClient::setClient()
{
    if (!m_socket.is_open()) return (false);
    m_address = m_socket.remote_endpoint().address().to_string();
    m_port = m_socket.remote_endpoint().port();

    return (true);
}

const std::string &TCPClient::getAddress() const
{ return (m_address); }

const unsigned int TCPClient::getPort() const
{ return (m_port); }

char *TCPClient::getPacket() const
{ return (m_packet); }

void TCPClient::setUsername(const std::string &username)
{
    m_username = username;
}

const std::string &TCPClient::getUsername() const
{ return (m_username); }

ByteBuffer &TCPClient::getBuffer()
{ return (buffer); }