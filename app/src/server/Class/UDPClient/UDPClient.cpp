/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** UDPClient
*/

#include "server/Class/UDPClient/UDPClient.hpp"

UDPClient::UDPClient()
{
    m_packet = new unsigned char[1024];
}

UDPClient::~UDPClient()
{
    if (m_packet) delete m_packet;
}

bool UDPClient::setClient()
{
    m_address = m_endpoint.address().to_string();
    m_port = m_endpoint.port();

    return (true);
}

const std::string &UDPClient::getAddress() const
{ return (m_address); }

const unsigned int UDPClient::getPort() const
{ return (m_port); }

unsigned char *UDPClient::getPacket() const
{ return (m_packet); }