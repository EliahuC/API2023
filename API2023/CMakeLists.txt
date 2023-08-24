cmake_minimum_required(VERSION 3.25)
project(API2023 C)

#Setting compiler
set(CXXFLAGS  -Wall -Wextra -Werror -std=gnu11 -lm -static -s)
set(CMAKE_CXX_FLAGS ${CXXFLAGS})


set(CMAKE_C_STANDARD 11)

add_executable(API2023 main.c)
