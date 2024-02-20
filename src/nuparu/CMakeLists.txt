# Needed in every CMakeLists.txt that forms a path to tests via
# add_subdirectory() calls.
enable_testing()

add_library("positions" SHARED "")
target_sources("positions"
  PRIVATE
    "positions.hpp"
    "positions.cpp"
  )
target_include_directories("positions"
PUBLIC
  ${Boost_INCLUDE_DIRS}
  ${LOCPROJ_INCLUDE_DIR}
)
add_library("nuparu::positions" ALIAS "positions")

add_executable("example_test" "")
target_sources("example_test"
  PRIVATE
    "example_test.cpp"
  )
target_include_directories("example_test"
  PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${LOCPROJ_INCLUDE_DIR}
  )
add_test("nuparu::example_test" "example_test")
