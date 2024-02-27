cmake_minimum_required(VERSION 3.26)
project(f_maze_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(f_maze_2
        common.h
        main.cxx
        maze.cxx
        maze.h
        mazerunner.cxx
        player.h
#        player_randommove.cxx
#        player_randommove.h
        ds_for_search.h)
add_library(player_randommove SHARED my_solution.cxx)

