cmake_minimum_required(VERSION 3.5)

project(qt-wayland-decorations-bradient-mkii VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED Core Gui WaylandClient)

set(PROJECT_SOURCES
    main.cpp
)

set(OUT_NAME bradient-mkii)
qt_add_library(${OUT_NAME} SHARED
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(${OUT_NAME} PRIVATE
    Qt6::Core
    Qt6::CorePrivate
    Qt6::Gui
    Qt6::GuiPrivate
    Qt6::WaylandClient
    Qt6::WaylandClientPrivate
)

qt_finalize_target(${OUT_NAME})
