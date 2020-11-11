/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** TestMessageHandler
*/

#ifndef TESTMESSAGEHANDLER_HPP_
#define TESTMESSAGEHANDLER_HPP_

#include "lib/Network/AMessageHandler.hpp"
#include "shared/Packet/TestPacket.hpp"
#include <string>
#include <iostream>

class TestMessageHandler : public AMessageHandler<TestPacket> {
    public:
        TestMessageHandler() {};
        ~TestMessageHandler() {};

        void onMessage(NetworkHandler &handler, INetworkClient &client, TestPacket &testPacket) override {
            std::cout << "TestPacket On Message: " << testPacket.getMessage() << std::endl;
            handler.broadcast(TestPacket("IT WORKED"));
        };

    protected:
    private:
};

#endif /* !TESTMESSAGEHANDLER_HPP_ */
