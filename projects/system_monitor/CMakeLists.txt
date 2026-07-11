cmake_minimum_required(VERSION 3.16)

project(system_monitor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

# Content of downloaded design from Figma to Qt or similar
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
endif()

qt_add_executable(appsystem_monitor
    src/main.cpp
)

set_source_files_properties(qml/theme/Theme.qml
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(appsystem_monitor
    URI system_monitor
    QML_FILES
        qml/ui/Main.qml
        QML_FILES qml/theme/Theme.qml
        QML_FILES qml/theme/DarkPalette.qml
        QML_FILES qml/theme/LightPalette.qml
        QML_FILES qml/theme/Typography.qml
        QML_FILES qml/theme/Spacing.qml
)

qt_add_resources(appsystem_monitor
    PREFIX "/"
    FILES
        assets/fonts/Inter_18pt-Regular.ttf
        assets/fonts/Inter_18pt-Medium.ttf
        assets/fonts/Inter_18pt-SemiBold.ttf
        assets/fonts/Inter_18pt-Bold.ttf
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appsystem_monitor PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appsystem_monitor
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appsystem_monitor
    PRIVATE Qt6::Quick
)

install(TARGETS appsystem_monitor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_include_directories(appsystem_monitor
    PRIVATE  ${CMAKE_CURRENT_LIST_DIR}/src
)
