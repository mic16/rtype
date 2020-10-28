/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** AServer.test
*/

#include <boost/test/unit_test.hpp>
#include "server/Class/AServer/AServer.hpp"

BOOST_AUTO_TEST_SUITE(TestsAServer)

BOOST_AUTO_TEST_CASE(class_creation)
{
  int i = 1;
  BOOST_TEST(i);
  BOOST_TEST(i == 2);
}

BOOST_AUTO_TEST_SUITE_END()