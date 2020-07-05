

set(RESOURCE_FILES "")

if (WIN32)
    set(RESOURCE_FILES
            ${RESOURCE_FILES}
            "${home_env_iot_dashboard_RESOURCE_DIR}/HomeEnvDashboardIcon.ico"
            "${home_env_iot_dashboard_RESOURCE_DIR}/resources.rc"
            )
elseif(APPLE)
    set(RESOURCE_FILES
            ${RESOURCE_FILES}
            ${home_env_iot_dashboard_RESOURCE_DIR}/HomeEnvDashboardIcon.icns
            )
endif()


set(SOURCE_FILES
        environemental_data.cpp
        environemental_data.hpp
        rest_api_interface.cpp
        rest_api_interface.hpp
        ogl_widget.cpp
        ogl_widget.hpp
        )


add_executable(home_env_iot_desktop
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${SOURCE_FILES}
        ${RESOURCE_FILES}
        )

target_link_libraries(home_env_iot_desktop
        PRIVATE
        cpprestsdk::cpprest
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
        OpenGL::GL
        OpenGL::GLU
        )
set_target_properties(home_env_iot_desktop
        PROPERTIES
        CXX_STANDARD    17
        VERSION         ${PROJECT_VERSION}
        OUTPUT_NAME     "HomeEnvDashboard"
        )

if (WIN32)

    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")


    add_custom_command(TARGET home_env_iot_desktop POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}"
            --verbose 0
            --no-compiler-runtime
            \"$<TARGET_FILE:home_env_iot_desktop>\"
            COMMENT "Deploying Qt..."
            )

endif(WIN32)
if(APPLE)

    set_target_properties(home_env_iot_desktop
            PROPERTIES
            MACOSX_BUNDLE                       TRUE
            MACOSX_BUNDLE_INFO_PLIST            ${home_env_iot_dashboard_RESOURCE_DIR}/MacOSXBundleInfo.plist.in
            MACOSX_BUNDLE_BUNDLE_NAME           "HomeEnvDashboard"
            MACOSX_BUNDLE_BUNDLE_VERSION        ${PROJECT_VERSION}
            MACOSX_BUNDLE_LONG_VERSION_STRING   ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING  ${PROJECT_VERSION}
            MACOSX_BUNDLE_ICON_FILE             HomeEnvDashboardIcon.icns
            MACOSX_BUNDLE_COPYRIGHT             "Copyright © 2020 David Oberacker"
            MACOSX_FRAMEWORK_IDENTIFIER         "me.d4ve.home.Dashboard"
            RESOURCE                            ${RESOURCE_FILES}
            )


    find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${_qt_bin_dir}")
    add_custom_command(TARGET home_env_iot_desktop POST_BUILD
            COMMAND "${MACDEPLOYQT_EXECUTABLE}"
            \"$<TARGET_BUNDLE_DIR:home_env_iot_desktop>\"
            -always-overwrite
            COMMENT "Deploying Qt..."
            )
endif(APPLE)