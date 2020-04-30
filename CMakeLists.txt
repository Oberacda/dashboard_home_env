cmake_minimum_required(VERSION 3.16)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(home_env_iot_dashboard
        VERSION 1.0.0.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)
find_package(cpprestsdk REQUIRED)

get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)

set(home_env_iot_dashboard_RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(home_env_iot_dashboard_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${home_env_iot_dashboard_SOURCE_DIR})
add_subdirectory(${home_env_iot_dashboard_SOURCE_DIR})






