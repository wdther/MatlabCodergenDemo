cmake_minimum_required(VERSION 3.16)
project(examples)

set(CMAKE_CXX_STANDARD 14)




include_directories(.)
link_directories(.)

add_executable(examples
        main.cpp
        )
target_link_libraries(examples
        coder_foo)




