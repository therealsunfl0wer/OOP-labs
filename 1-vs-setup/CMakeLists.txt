cmake_minimum_required(VERSION 3.20)
project(lab1-vs-setup LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(lab1 src/main.cpp)
target_link_libraries(lab1 PRIVATE Qt6::Widgets)
