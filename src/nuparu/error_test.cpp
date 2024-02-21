#define BOOST_TEST_MODULE nuparu_error_test

#include <boost/algorithm/string.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <string>

#include "nuparu/error.hpp"

using ::nuparu::Error;
using ::nuparu::ErrorCode;
using ::nuparu::ErrorOr;

BOOST_AUTO_TEST_SUITE(ErrorTestSuite)

BOOST_AUTO_TEST_CASE(SimpleError)
{
  Error error(ErrorCode::NONE);
  BOOST_TEST(error.Code() == ErrorCode::NONE);
  BOOST_TEST(error.None());

  error = Error(ErrorCode::INVALID_ARGUMENT);
  BOOST_TEST(error.Code() == ErrorCode::INVALID_ARGUMENT);
  BOOST_TEST(!error.None());
}

BOOST_AUTO_TEST_CASE(ErrorDebugString)
{
  Error error(ErrorCode::INVALID_ARGUMENT, "unloved and unwanted");
  auto debug_string = error.DebugString();
  BOOST_TEST(boost::algorithm::contains(debug_string, "INVALID_ARGUMENT"));
  BOOST_TEST(boost::algorithm::contains(debug_string, "unloved and unwanted"));

  error.PushTrace("alone and abandoned");
  debug_string = error.DebugString();
  BOOST_TEST(boost::algorithm::contains(debug_string, "INVALID_ARGUMENT"));
  BOOST_TEST(boost::algorithm::contains(debug_string, "unloved and unwanted"));
  BOOST_TEST(boost::algorithm::contains(debug_string, "alone and abandoned"));
}

BOOST_AUTO_TEST_SUITE_END()
