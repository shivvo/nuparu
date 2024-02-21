#include <cstdint>
#define BOOST_TEST_MODULE nuparu_error_test

#include <boost/algorithm/string.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <string>

#include "nuparu/error.hpp"

namespace
{

using ::nuparu::Error;
using ::nuparu::ErrorCode;
using ::nuparu::ErrorOr;

Error ErrorPassthroughFunction2(const Error &error)
{
  TRY(error);
  return error;
}

Error ErrorPassThroughFunction1(const Error &error)
{
  TRY(ErrorPassthroughFunction2(error));
  return error;
}

Error MaybeMutateAndPassThroughError(const Error &error)
{
  if (!error.None())
  {
    auto mutated_error = error;
    mutated_error.Update(ErrorCode::INTERNAL, "mutated to internal");
    return ErrorPassThroughFunction1(mutated_error);
  }
  return error;
}
} // namespace

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

BOOST_AUTO_TEST_CASE(ErrorMutations)
{
  Error error(ErrorCode::INVALID_ARGUMENT, "unloved and unwanted");
  auto debug_string = error.DebugString();
  BOOST_TEST(boost::algorithm::contains(debug_string, "INVALID_ARGUMENT"));
  BOOST_TEST(boost::algorithm::contains(debug_string, "unloved and unwanted"));

  auto mutated_error = MaybeMutateAndPassThroughError(error);
  debug_string = mutated_error.DebugString();
  BOOST_TEST(boost::algorithm::contains(debug_string, "INVALID_ARGUMENT"));
  BOOST_TEST(boost::algorithm::contains(debug_string, "unloved and unwanted"));
  BOOST_TEST(
      boost::algorithm::contains(debug_string, "ErrorPassThroughFunction1"));
  BOOST_TEST(
      boost::algorithm::contains(debug_string, "ErrorPassthroughFunction2"));
  BOOST_TEST(boost::algorithm::contains(debug_string, "INTERNAL"));
  BOOST_TEST(boost::algorithm::contains(debug_string, "mutated to internal"));
}

BOOST_AUTO_TEST_CASE(ErrorOrBaseCases)
{

  ErrorOr<int64_t> error_or_contains_error = Error(ErrorCode::INTERNAL);
  BOOST_TEST(!error_or_contains_error.Err().None());

  ErrorOr<int64_t> error_or_contains_value = 6;
  BOOST_TEST(error_or_contains_value.Err().None());
  BOOST_TEST(error_or_contains_value.Value() == 6);
};

BOOST_AUTO_TEST_SUITE_END()
