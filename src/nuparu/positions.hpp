#ifndef NUPARU_POSITIONS
#define NUPARU_POSITIONS

#include <cstdint>
#include <vector>

namespace nuparu {

// Given a 1D array of fixed size, or region, store an ordered list of fixed
// size (between 1 and region size) of indices, or positions, of interest within
// that region. For fixed region size and positions size, there are a finite
// number of positions and the possible values comprise the "positions space"
// for that region size and positions size.
class Positions {
public:
  Positions(std::vector<int32_t> positions, int32_t region_size)
      : m_positions(positions), m_positions_size(positions.size()),
        m_region_size(region_size) {}

  int32_t GetPosition(int position_index) {
    return m_positions[position_index];
  }

  // Increment and decrement operations.
  void Next();
  void Prev();

  // Determine if counters are in start or end states.
  bool IsBegin();
  bool IsEnd();

private:
  int GetMinValueForCounterAtIndex(int index);
  int GetMaxValueForCounterAtIndex(int index);

  std::vector<int32_t> m_positions;
  int32_t m_positions_size;
  int32_t m_region_size;
};

} // namespace nuparu

#endif
