cmake_minimum_required(VERSION 3.14)
project(ChessCPP)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_executable(ChessCPP main.cpp)

target_link_libraries(ChessCPP sfml-graphics sfml-audio)