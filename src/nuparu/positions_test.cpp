#define BOOST_TEST_MODULE nuparu_positions_test

#include <boost/dynamic_bitset.hpp>
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include <vector>

#include "nuparu/positions.hpp"

namespace
{
using ::nuparu::Positions;

void TestPositionsSpace(Positions positions, // Copy intended
                        std::vector<std::vector<int>> positions_space)
{
  for (int i = 0; i < positions_space.size(); i++)
  {
    if (i == 0)
    {
      BOOST_TEST(positions.IsBegin());
    }
    BOOST_TEST(positions.GetAllPositions() == positions_space[i],
               boost::test_tools::per_element());
    positions.Next();
    if (i == positions_space.size())
    {
      BOOST_TEST(positions.IsEnd());
    }
  }
  {
    std::vector<int32_t> end_positions = positions.GetAllPositions();
    positions.Next();
    BOOST_TEST(positions.GetAllPositions() == end_positions,
               boost::test_tools::per_element());
  }
  for (int i = positions_space.size() - 1; i >= 0; i--)
  {

    if (i == positions_space.size() - 1)
    {
      BOOST_TEST(positions.IsEnd());
    }
    BOOST_TEST(positions.GetAllPositions() == positions_space[i],
               boost::test_tools::per_element());
    positions.Prev();
    if (i == 0)
    {
      BOOST_TEST(positions.IsBegin());
    }
  }
  {
    std::vector<int32_t> begin_positions = positions.GetAllPositions();
    positions.Prev();
    BOOST_TEST(positions.GetAllPositions() == begin_positions,
               boost::test_tools::per_element());
  }
}

} // namespace

BOOST_AUTO_TEST_SUITE(PositionsTestSuite)

BOOST_AUTO_TEST_CASE(RegionsSize1)
{
  std::vector<std::vector<int>> positions_space = {{0}, {1}, {2}};
  Positions positions({0}, 3);
  TestPositionsSpace(positions, positions_space);
}

BOOST_AUTO_TEST_SUITE_END()
