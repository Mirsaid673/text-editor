cmake_minimum_required(VERSION 3.10)
project(QT)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets)

add_executable(out main.cpp editor.h editor.cpp)
target_link_libraries(out PUBLIC Qt6::Widgets)