cmake_minimum_required(VERSION 3.20)
project(Lab6-object3 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets)

add_executable(object3 main.cpp)
target_include_directories(object3 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/..)
target_link_libraries(object3 PRIVATE Qt6::Core Qt6::Network Qt6::Widgets)
set_target_properties(object3 PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                      ${CMAKE_BINARY_DIR}/6-message-driven-system)
install(TARGETS object3 RUNTIME DESTINATION bin)

add_custom_target(run-object3
    COMMAND object3
    DEPENDS object3
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    USES_TERMINAL
)
