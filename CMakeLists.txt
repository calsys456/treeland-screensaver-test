cmake_minimum_required(VERSION 3.25.0)

project(treeland-screensaver-test LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core DBus)

add_executable(treeland-screensaver-test
    main.cpp
)

target_link_libraries(treeland-screensaver-test
    Qt6::Core
    Qt6::DBus
)
