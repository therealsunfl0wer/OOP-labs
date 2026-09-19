cmake_minimum_required(VERSION 3.20)
project(oop-labs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Qt handles moc/uic/rcc automatically
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Each lab is a standalone CMake project with its own executable target.
# Comment out any you don't want built yet.
add_subdirectory(1-vs-setup)
add_subdirectory(2-shape-editor)
# add_subdirectory(3-ui-widgets)
# add_subdirectory(4-editor-refactor)
# add_subdirectory(5-multiwindow-editor)
# add_subdirectory(6-message-driven-system/sender)
# add_subdirectory(6-message-driven-system/receiver)

# Individual project (RGR) — only buildable once you've picked a topic
# and populated rgr-project/src. Comment out until then.
# add_subdirectory(rgr-project)
