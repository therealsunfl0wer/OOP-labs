cmake_minimum_required(VERSION 3.20)
project(lab-3-ui-widgets LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/*.h)

add_executable(lab3 ${SOURCES} ${HEADERS})
target_include_directories(lab3 PRIVATE include)
target_link_libraries(lab3 PRIVATE Qt6::Widgets)
