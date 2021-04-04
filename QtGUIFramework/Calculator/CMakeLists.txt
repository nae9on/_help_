cmake_minimum_required(VERSION 3.16)

project(project_Calculator)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core)
find_package(Qt5Widgets)

add_executable(
"${PROJECT_NAME}"
main.cpp
button.h
button.cpp
calculator.h
calculator.cpp
)

target_link_libraries("${PROJECT_NAME}" Qt5::Core Qt5::Widgets)
