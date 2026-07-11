cmake_minimum_required(VERSION 3.16)

project(file_viewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Concurrent)

qt_standard_project_setup(REQUIRES 6.8)

# Content of downloaded design from Figma to Qt or similar
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
endif()

qt_add_executable(appfile_viewer
    main.cpp
    flux/action.h flux/dispatcher.h
    flux/middleware.h flux/store.h
    src/fileparser.h src/fileparser.cpp
    src/itemdata.h src/itemdata.cpp
    src/itemstore.h src/itemstore.cpp
    src/itemmodel.h src/itemmodel.cpp
    src/itemviewmodel.h src/itemviewmodel.cpp
    src/actionprovider.h src/actionprovider.cpp
    src/ItemAction.h src/DataType.h
)

qt_add_qml_module(appfile_viewer
    URI file_viewer
    QML_FILES
        qml/Main.qml
        qml/ErrorDialog.qml
        qml/ItemTable.qml
        qml/OpenFileButton.qml
        qml/SearchBar.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appfile_viewer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appfile_viewer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appfile_viewer
    PRIVATE Qt6::Quick Qt6::Concurrent
)

target_include_directories (appfile_viewer
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src ${CMAKE_CURRENT_LIST_DIR}/flux
)

install(TARGETS appfile_viewer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
