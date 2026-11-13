cmake_minimum_required(VERSION 3.20)
project(Lab6-object2 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets)

add_executable(object2 main.cpp)
target_include_directories(object2 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/..)
target_link_libraries(object2 PRIVATE Qt6::Core Qt6::Network Qt6::Widgets)
set_target_properties(object2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                      ${CMAKE_BINARY_DIR}/6-message-driven-system)
install(TARGETS object2 RUNTIME DESTINATION bin)

add_custom_target(run-object2
    COMMAND object2
    DEPENDS object2
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    USES_TERMINAL
)
