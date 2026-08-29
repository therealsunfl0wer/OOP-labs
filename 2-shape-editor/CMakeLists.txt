cmake_minimum_required(VERSION 3.20)
project(Lab2 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/*.h)

add_executable(lab2 ${SOURCES} ${HEADERS})
target_include_directories(lab2 PRIVATE include)
target_link_libraries(lab2 PRIVATE Qt6::Widgets)

add_custom_target(run-lab2
    COMMAND lab2
    DEPENDS lab2
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    USES_TERMINAL
)
