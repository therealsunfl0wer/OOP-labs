cmake_minimum_required(VERSION 3.16)
project(Lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)


add_executable(lab1
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/module1.cpp
    src/module1.h
    src/module2.cpp
    src/module2.h
    src/groups.cpp
    src/groups.h
)

target_link_libraries(lab1 PRIVATE Qt6::Widgets)
