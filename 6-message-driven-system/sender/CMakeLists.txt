cmake_minimum_required(VERSION 3.20)
project(Lab6-sender LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

add_executable(lab6-sender main.cpp)
target_link_libraries(lab6-sender PRIVATE Qt6::Core Qt6::Network)

add_custom_target(run-lab6-sender
    COMMAND lab6-sender
    DEPENDS lab6-sender
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    USES_TERMINAL
)
