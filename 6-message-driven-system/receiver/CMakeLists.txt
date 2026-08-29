cmake_minimum_required(VERSION 3.20)
project(Lab6-receiver LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

add_executable(lab6-receiver main.cpp)
target_link_libraries(lab6-receiver PRIVATE Qt6::Core Qt6::Network)

add_custom_target(run-lab6-receiver
    COMMAND lab6-receiver
    DEPENDS lab6-receiver
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    USES_TERMINAL
)
