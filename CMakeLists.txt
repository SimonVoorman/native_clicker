cmake_minimum_required(VERSION 3.13)
project(auto_clicker)

set(CMAKE_CXX_STANDARD 17)

add_executable(auto_clicker source/main.cpp extern/lazy_importer.h source/util/values.cpp source/util/values.hpp source/includes.hpp source/util/c_rand_util.hpp source/util/c_console.cpp source/util/c_console.hpp extern/xorstr.hpp source/util/c_win_api.cpp source/util/c_win_api.hpp source/clicker/c_clicker.cpp source/clicker/c_clicker.hpp)