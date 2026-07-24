cmake_minimum_required(VERSION 3.25)
project(NodeTesting LANGUAGES CXX)

# 1. Enforce native C++23 rules (Now perfectly supported by your CMake version)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add standard diagnostic warnings
add_compile_options(-g -Wall -Wextra)

# Find the Catch2 testing library package
find_package(Catch2 3 REQUIRED)

# Gather external object files from the parent directory
file(GLOB NODE_OBJECTS "../*.o")

# -------------------------------------------------------------
# TARGET 1: test_node_1.out
# -------------------------------------------------------------
add_executable(test_node_1.out test_node_1.cc ${NODE_OBJECTS})
target_link_libraries(test_node_1.out PRIVATE Catch2::Catch2WithMain)

# -------------------------------------------------------------
# TARGET 2: test_node_2.out
# -------------------------------------------------------------
add_executable(test_node_2.out test_node_2.cc ${NODE_OBJECTS})
target_link_libraries(test_node_2.out PRIVATE Catch2::Catch2WithMain)

# -------------------------------------------------------------
# TARGET 3: main.out (Uses readline instead of Catch2)
# -------------------------------------------------------------
# add_executable(main.out main.cc ${NODE_OBJECTS})
# target_link_libraries(main.out PRIVATE readline)

