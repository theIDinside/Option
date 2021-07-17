cmake_minimum_required(VERSION 3.19)
project(Option LANGUAGES CXX)
set(EXPORT_COMPILE_COMMANDS ON)

set(SOURCES include/option.hpp)
set(CMAKE_CXX_STANDARD REQUIRED 20)


add_library(Option INTERFACE 
    include/option.hpp
)
set_target_properties(Option PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED TRUE)

target_include_directories(Option INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/Option>
)

add_executable(test tests/main.cpp)
set_target_properties(test PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED TRUE)
target_link_libraries(test Option)

