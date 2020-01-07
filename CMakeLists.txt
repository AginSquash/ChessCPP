cmake_minimum_required(VERSION 3.9)
project(ChessCPP)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

set(APP_NAME ChessCPP)

add_executable(${APP_NAME} main.cpp DataLoading.cpp DataLoading.h configWorker.cpp configWorker.h settings.hpp settings.cpp debug_func.cpp debug_func.hpp figure_movement.cpp figure_movement.hpp figure_rules.cpp figure_rules.hpp types.h movement.hpp movement.cpp)

target_link_libraries(ChessCPP sfml-graphics sfml-audio)

