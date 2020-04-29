cmake_minimum_required(VERSION 3.16)
project(home_env_iot_desktop)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

find_package(cpprestsdk REQUIRED)

add_executable(home_env_iot_desktop main.cpp)
target_link_libraries(home_env_iot_desktop
        PRIVATE
        cpprestsdk::cpprest
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
        )