/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** AServer.test
*/

#include <boost/test/unit_test.hpp>
#include "server/Class/AServer/AServer.hpp"

BOOST_AUTO_TEST_SUITE(TestsAServer)

BOOST_AUTO_TEST_CASE(configuration)
{
  AServer *server = new AServer();

  BOOST_TEST(server->getPort() == 0);

  server->configure(3000);

  BOOST_TEST(server->getPort() == 3000);
  if (server) delete server;
}

BOOST_AUTO_TEST_SUITE_END()