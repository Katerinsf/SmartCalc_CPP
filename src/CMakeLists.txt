cmake_minimum_required(VERSION 3.5)

project(view VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 
#add_subdirectory(librarys/QCustomPlot-library)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS PrintSupport)

set(PROJECT_SOURCES
        main.cc
        view/view.cc
        view/view.h
        view/view.ui
        model/model.cc
        model/model.h
        controller/controller.cc
        controller/controller.h
        view/qcustomplot.cc
        view/qcustomplot.h
        view/graph.h
        view/graph.cc
        view/graph.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(view
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET view APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(view SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(view
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(view PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(view PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

#target_link_libraries(SmartCalc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(${PROJECT_NAME} PRIVATE qcustomplot)
#target_compile_definitions(${PROJECT_NAME} PRIVATE QCUSTOMPLOT_USE_LIBRARY)

set_target_properties(view PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(view)
endif()
