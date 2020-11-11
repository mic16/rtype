/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** TestMessageHandler
*/

#ifndef TESTMESSAGEHANDLERCLIENT_HPP_
#define TESTMESSAGEHANDLERCLIENT_HPP_

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/TestPacket.hpp"
#include <string>
#include <iostream>

class TestMessageClientHandler : public AMessageHandler<TestPacket> {
    public:
        TestMessageClientHandler() {};
        ~TestMessageClientHandler() {};

        void onMessage(NetworkHandler &handler, INetworkClient &client, TestPacket &testPacket) override {
            std::cout << "TestPacket On Message: " << testPacket.getMessage() << std::endl;
        };

    protected:
    private:
};

#endif /* !TESTMESSAGEHANDLERCLIENT_HPP_ */
