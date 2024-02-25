#cmake_minimum_required(VERSION 3.5)

#project(qt-standard-icon VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
find_package(fmt REQUIRED)

set(PROJECT_SOURCES
	main.cpp
)

add_executable(${PROJECT_NAME}
	${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	Qt6::Core
	Qt6::Gui
	Qt6::Widgets
	fmt::fmt
)
