cmake_minimum_required(VERSION 3.16)

project(to_do_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appto_do_app
    src/main.cpp
    src/Task.h
    src/taskstorage.h src/taskstorage.cpp
)

qt_add_qml_module(appto_do_app
    URI to_do_app
    QML_FILES
        qml/Main.qml
        qml/TaskDelegate.qml
        qml/FilterBar.qml

    SOURCES
        src/taskmodel.h src/taskmodel.cpp
        src/taskfilterproxy.h src/taskfilterproxy.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appto_do_app PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appto_do_app
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appto_do_app
    PRIVATE Qt6::Quick
)

target_include_directories(appto_do_app PRIVATE
    src/
)

install(TARGETS appto_do_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
