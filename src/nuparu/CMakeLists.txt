# Needed in every CMakeLists.txt that forms a path to tests via
# add_subdirectory() calls.
enable_testing()

add_library("error" SHARED "")
target_sources("error"
  PRIVATE
    "error.hpp"
    "error.cpp"
  )
add_library("nuparu::error" ALIAS "error")

add_executable("error_test" "")
target_sources("error_test"
  PRIVATE
    "error_test.cpp"
  )
target_link_libraries("error_test"
  "nuparu::error"
  )
add_test("nuparu::error_test" "error_test")

add_library("positions" SHARED "")
target_sources("positions"
  PRIVATE
    "positions.hpp"
    "positions.cpp"
  )
target_link_libraries("positions"
  "nuparu::error"
  )
add_library("nuparu::positions" ALIAS "positions")

add_executable("positions_test" "")
target_sources("positions_test"
  PRIVATE
    "positions_test.cpp"
  )
target_link_libraries("positions_test"
  "nuparu::positions"
  )
add_test("nuparu::positions_test" "positions_test")

add_executable("example_test" "")
target_sources("example_test"
  PRIVATE
    "example_test.cpp"
  )
add_test("nuparu::example_test" "example_test")
