cmake_minimum_required(VERSION 3.14)

set(this branch_and_bound)

project(${this})

set(CMAKE_CXX_STANDARD 14)
set(${this} C CXX)

add_subdirectory(src)

# enable_testing()
add_executable(${this} src/main.cpp)

target_link_libraries(${this} PUBLIC
  BranchAndBound
  Data
  Hungarian
)

target_include_directories(${this} PUBLIC
  ${CMAKE_SOURCE_DIR}/include/models/
)
