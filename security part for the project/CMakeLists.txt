cmake_minimum_required(VERSION 3.10)

project(security_part_for_the_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(security_part_for_the_project
        main.cpp
        SecurityAPI.cpp
        SecurityAPI.h
        sha256.cpp
        sha256.h
)
