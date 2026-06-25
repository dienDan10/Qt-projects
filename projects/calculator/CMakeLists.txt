cmake_minimum_required(VERSION 3.16)

project(calculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

# Content of downloaded design from Figma to Qt or similar
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
endif()

qt_add_executable(appcalculator
    main.cpp
    flux/action.h flux/dispatcher.h
    flux/middleware.h flux/store.h
    src/calculatoraction.h
    src/calculatorengine.h src/calculatorengine.cpp
)

set_source_files_properties(qml/Config.qml
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE)
qt_add_qml_module(appcalculator
    URI calculator
    QML_FILES
        qml/Main.qml
        qml/NumberBtn.qml
        qml/OperatorBtn.qml
        qml/Config.qml
        qml/Keyboard.qml
        qml/BackspaceBtn.qml

    SOURCES
        src/calculatoractionprovider.h src/calculatoractionprovider.cpp
        
    RESOURCES
        assets/images/backspace.svg
        assets/images/backspace_fill.svg
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appcalculator PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appcalculator
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appcalculator
    PRIVATE Qt6::Quick
)

install(TARGETS appcalculator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_include_directories(appcalculator
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src ${CMAKE_CURRENT_LIST_DIR}/flux
)