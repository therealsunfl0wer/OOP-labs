cmake_minimum_required(VERSION 3.20)
project(Lab6 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets)

add_executable(lab6 main.cpp)
target_include_directories(lab6 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/..)
target_link_libraries(lab6 PRIVATE Qt6::Core Qt6::Network Qt6::Widgets)
set_target_properties(lab6 PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                      ${CMAKE_BINARY_DIR}/6-message-driven-system)
install(TARGETS lab6 RUNTIME DESTINATION bin)

add_custom_target(run-lab6
    COMMAND lab6
    DEPENDS lab6
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    USES_TERMINAL
)
