cmake_minimum_required(VERSION 3.10)

project(movfuscator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

include_directories(include)

add_executable(movfuscator 
    src/main.cpp
    src/aritm.cpp
    src/cmp.cpp
    src/logic.cpp
    src/mov.cpp
    src/movinit.cpp
    src/push.cpp
    src/jmp.cpp
    src/lea.cpp
    src/mul.cpp
)

