cmake_minimum_required(VERSION 3.7)
project(proj1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cc)

add_executable(proj1 ${SOURCE_FILES})