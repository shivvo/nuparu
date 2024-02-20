cmake_minimum_required(VERSION 3.0.0)

project(nuparu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Copy compile_commands.json to root directory.
add_custom_target(
    copy-compile-commands ALL
    ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_LIST_DIR}
    )

# Boost
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
find_package(Boost 1.71.0 REQUIRED)

# Set local include directories
set(LOCAL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src)

# Needed in every CMakeLists.txt that forms a path to tests via
# add_subdirectory() calls.
enable_testing()
add_subdirectory(src/nuparu)
