cmake_minimum_required(VERSION 3.0.0)

project(nuparu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Boost
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
find_package(Boost 1.71.0 REQUIRED)

# Needed in every CMakeLists.txt that forms a path to tests via
# add_subdirectory() calls.
enable_testing()
add_subdirectory(src/nuparu)
