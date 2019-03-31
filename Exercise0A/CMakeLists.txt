cmake_minimum_required(VERSION 3.13)
project(Exercise0A C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(queue)
include_directories(stack)

add_executable(Exercise0A
        queue/queue.c
        queue/queue.h
        stack/stack.c
        stack/stack.h
        main.c
        utility.c
        utility.h)
