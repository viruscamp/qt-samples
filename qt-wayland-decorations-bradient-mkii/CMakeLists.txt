cmake_minimum_required(VERSION 3.5)

project(qt-wayland-decorations-bradient-mkii VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(USE_QT6 1)
if (DEFINED USE_QT6)
    find_package(QT NAMES Qt6 REQUIRED Core)
else()
    find_package(QT NAMES Qt5 REQUIRED Core)
endif()
find_package(Qt${QT_VERSION_MAJOR} REQUIRED Core Gui WaylandClient)

set(PROJECT_SOURCES
    main.cpp
)

include_directories(
    /usr/include/qt6/QtCore/${QT_VERSION}
    /usr/include/qt6/QtGui/${QT_VERSION}
    /usr/include/qt6/QtGui/${QT_VERSION}/QtGui
    /usr/include/qt6/QtWaylandClient/${QT_VERSION}
    /usr/include/qt6/QtWaylandGlobal/${QT_VERSION}
)

set(OUT_NAME bradient-mkii)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_library(${OUT_NAME} SHARED
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_library(${OUT_NAME} SHARED
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(${OUT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::WaylandClient
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_finalize_target(${OUT_NAME})
endif()
