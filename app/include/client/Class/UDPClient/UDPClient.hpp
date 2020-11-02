/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** UDPClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

class UDPClient
{
public:
    UDPClient(
        boost::asio::io_service& io_service, 
        const std::string& host, 
        const std::string& port
    ) : io_service_(io_service), socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)) {
        boost::asio::ip::udp::resolver resolver(io_service_);
        boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), host, port);
        boost::asio::ip::udp::resolver::iterator iter = resolver.resolve(query);
        endpoint_ = *iter;
    }

    ~UDPClient()
    {
        socket_.close();
    }

    void send(const std::string& msg) {
        socket_.send_to(boost::asio::buffer(msg, msg.size()), endpoint_);
    }

private:
    boost::asio::io_service& io_service_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint endpoint_;
};

#endif /* !UDPCLIENT_HPP_ */