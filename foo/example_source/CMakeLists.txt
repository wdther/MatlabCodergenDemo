cmake_minimum_required(VERSION 3.16)
project(examples)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(examples
        main.cpp
        coder_foo.cpp
        coder_foo_terminate.cpp
        )



