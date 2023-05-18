cmake_minimum_required(VERSION 3.5)

project(squares LANGUAGES CXX)

add_compile_options(-Wall -g)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

add_executable(squares
  main.cpp
  mainwindow.cpp
  segment.cpp
  ${TS_FILES}
)

target_link_libraries(squares  PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
