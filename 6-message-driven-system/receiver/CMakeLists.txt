cmake_minimum_required(VERSION 3.20)
project(lab6-receiver LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

add_executable(lab6-receiver main.cpp)
target_link_libraries(lab6-receiver PRIVATE Qt6::Core Qt6::Network)
