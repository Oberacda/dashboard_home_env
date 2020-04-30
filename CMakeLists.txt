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
get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)

if (WIN32)

    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
    add_custom_command(TARGET home_env_iot_desktop POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E
            env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
            --verbose 0
            --no-compiler-runtime
            \"$<TARGET_FILE:home_env_iot_desktop>\"
            COMMENT "Deploying Qt..."
            )

endif(WIN32)
if(APPLE)

    set_target_properties(home_env_iot_desktop
            PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/MacOSXBundleInfo.plist.in
    )
    find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${_qt_bin_dir}")
    add_custom_command(TARGET home_env_iot_desktop POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E
            env PATH="${_qt_bin_dir}" "${MACDEPLOYQT_EXECUTABLE}"
            \"$<TARGET_FILE_DIR:home_env_iot_desktop>\"
            -verbose=0
            -always-overwrite
            COMMENT "Deploying Qt..."
            )
endif(APPLE)

