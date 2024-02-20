#include "nuparu/positions.hpp"

namespace nuparu {

int Positions::GetMinValueForCounterAtIndex(int index) {
  if (index == 0)
    return 0;
  return m_positions[index - 1];
}
int Positions::GetMaxValueForCounterAtIndex(int index) {
  return m_region_size - m_positions.size() + index;
}

void Positions::Next() {
  if (IsEnd())
    return;

  int current_counter_left_index = 0;

  // Get the right index from the left index.
  auto GetRightFromLeftIndex = [this, &current_counter_left_index]() {
    return m_positions.size() - current_counter_left_index - 1;
  };

  // Iterate through counter leftward from that last counter. Update the counter
  // values.
  while (current_counter_left_index != m_positions.size()) {
    // If counter can be incremented, then increment it and break;
    if (m_positions[GetRightFromLeftIndex()] + 1 <=
        GetMaxValueForCounterAtIndex(GetRightFromLeftIndex())) {
      m_positions[GetRightFromLeftIndex()]++;
      break;
    }

    // Move left index leftward.
    current_counter_left_index++;
  }

  // If necessary, move rightward and update counters.
  if (current_counter_left_index != 0) {
    while (current_counter_left_index > 0) {
      int prev_counter_value = m_positions[GetRightFromLeftIndex()];
      current_counter_left_index--;
      m_positions[GetRightFromLeftIndex()] = prev_counter_value + 1;
    }
  }
}

void Positions::Prev() {
  if (IsBegin())
    return;

  int current_counter_left_index = 0;

  // Get the right index from the left index.
  auto GetRightFromLeftIndex = [this, &current_counter_left_index]() {
    return m_positions.size() - current_counter_left_index - 1;
  };

  // Iterate through counter leftward from that last counter. Update the counter
  // values.
  while (current_counter_left_index != m_positions.size()) {
    // If counter can be decremented, then decremented it and break;
    if (m_positions[GetRightFromLeftIndex()] - 1 >
        GetMinValueForCounterAtIndex(GetRightFromLeftIndex())) {
      m_positions[GetRightFromLeftIndex()]--;
      break;
    }

    // Move left index leftward.
    current_counter_left_index++;
  }

  // If necessary, move rightward and update counters.
  if (current_counter_left_index != 0) {
    while (current_counter_left_index > 0) {
      current_counter_left_index--;
      m_positions[GetRightFromLeftIndex()] =
          GetMaxValueForCounterAtIndex(GetRightFromLeftIndex());
    }
  }
}

bool Positions::IsBegin() {
  return m_positions[m_positions.size() - 1] == m_positions.size() - 1;
}

bool Positions::IsEnd() {
  return m_positions[0] == m_region_size - m_positions.size();
}

} // namespace nuparu
