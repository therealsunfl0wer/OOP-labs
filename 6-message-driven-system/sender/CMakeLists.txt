cmake_minimum_required(VERSION 3.20)
project(lab6-sender LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

add_executable(lab6-sender main.cpp)
target_link_libraries(lab6-sender PRIVATE Qt6::Core Qt6::Network)
