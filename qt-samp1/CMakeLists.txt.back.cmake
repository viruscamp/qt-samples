cmake_minimum_required(VERSION 3.5)         #需要的CMake最低版本

project(qt6_samp1 VERSION 0.1 LANGUAGES CXX)  #项目版本0.1, 编程语言是C++

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)       # UIC能被自动执行
set(CMAKE_AUTOMOC ON)       # MOC能被自动执行
set(CMAKE_AUTORCC ON)       # RCC能被自动执行

set(CMAKE_CXX_STANDARD 11)  #设置编译器需要满足的C++语言标准， 设置为 C++ 11
set(CMAKE_CXX_STANDARD_REQUIRED ON)  #要求编译器满足 C++标准

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
find_package(fmt REQUIRED)

set(PROJECT_SOURCES         #设置变量 PROJECT_SOURCES 等于下面的列表
        main.cpp            #也就是项目的源文件列表
        MainWindow.h
        MainWindow.cpp
        MainWindow.ui
)

qt_add_executable(qt6_samp1     #创建可执行文件
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}         #文件列表来源于前面定义的变量PROJECT_SOURCES
)


#设置目标可执行文件的属性，如MacOSX的Bundle标识符、版本号和短版本字符串，以及在Windows下作为可执行文件运行。
set_target_properties(qt6_samp1 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

qt_finalize_target(qt6_samp1)
