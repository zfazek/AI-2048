# cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..

project(ai-2048)

cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_FLAGS "-Wall -Werror -std=c++17 -g -O2")

add_executable(ai-2048
    Game.cc
    Table.cc
    main.cc
    )

enable_testing()

add_subdirectory(test)
